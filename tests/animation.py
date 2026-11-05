import matplotlib.pyplot as plt
import matplotlib.patches as patches
from matplotlib.animation import FuncAnimation
import pandas as pd
import numpy as np

FILE_NAME = "../wrapper/Numerical_data.csv"

# Select numerical integration method: "RK4" or "Eular"
METHOD = "RK4"


def read_and_display_csv(file_name):
    """Read Time and Position data from Numerical_data.csv."""

    print(f"Reading file: {file_name}...")

    try:
        df = pd.read_csv(file_name)

        # Remove spaces from column names
        df.columns = df.columns.str.strip()

        print("CSV columns:", df.columns.tolist())

        # Display first 10 rows for debugging
        print("\nFirst 10 CSV rows:")
        print(df.head(10).to_string(index=False))

        # Convert Time column to numeric
        df["Time"] = pd.to_numeric(
            df["Time"],
            errors="coerce"
        )

        # Remove rows with invalid Time
        df = df.dropna(
            subset=["Time"]
        ).reset_index(drop=True)

        TIME_DATA = df["Time"].to_numpy()

        # Check time differences
        time_diff = np.diff(TIME_DATA)

        print("\nNumber of rows:", len(TIME_DATA))
        print("First 10 time values:", TIME_DATA[:10])
        print("First 10 time differences:", time_diff[:10])

        if np.any(time_diff <= 0):
            bad_indices = np.where(time_diff <= 0)[0]

            print("\nInvalid time sequence detected:")

            for i in bad_indices[:10]:
                print(
                    f"Row {i}: "
                    f"{TIME_DATA[i]} -> {TIME_DATA[i + 1]}"
                )

            raise ValueError(
                "Time data must be strictly increasing."
            )

        return (
            TIME_DATA,
            df[f"Position_{METHOD}"].to_numpy()
        )

    except Exception as e:
        print(f"CSV loading failed: {e}")
        raise




TIME_DATA, POSITION_DATA = read_and_display_csv(FILE_NAME)

# Calculate animation interval from CSV time data
TIME_STEP = np.median(np.diff(TIME_DATA))
INTERVAL_MS = TIME_STEP * 1000


# ====================================================================
# 2. Animation Geometry
# ====================================================================

WALL_X = -0.2

MASS_WIDTH = 0.3
MASS_HEIGHT = 0.8

CENTER_Y_SPRING = 0
CENTER_Y_DAMPER = -0.4

DAMPER_HEIGHT = 0.2
PISTON_WIDTH = 0.05
PISTON_HEIGHT = DAMPER_HEIGHT * 0.9


def create_spring_shape(
    x_start, x_end, y_center,
    num_coils=15, coil_height=0.25
):
    """Generate spring coordinates."""

    length = x_end - x_start

    if length <= 0.001:
        return [x_start, x_end], [y_center, y_center]

    t = np.linspace(0.05, 0.95, num_coils)

    x_coords = x_start + t * length
    y_coords = (
        y_center
        + (coil_height / 2) * np.sin(2 * np.pi * t * 4)
    )

    x_coords = np.concatenate([[x_start], x_coords, [x_end]])
    y_coords = np.concatenate([[y_center], y_coords, [y_center]])

    return x_coords, y_coords


# ====================================================================
# 3. Plot Environment
# ====================================================================

fig, ax = plt.subplots(figsize=(10, 6))

# Dynamic X-axis range
min_x_display = min(0, np.min(POSITION_DATA)) - MASS_WIDTH
max_x_display = np.max(POSITION_DATA) + MASS_WIDTH + 0.5

ax.set_xlim(WALL_X - 0.1, max(max_x_display, 1.0))
ax.set_ylim(-1.0, 1.0)

ax.set_aspect("equal")
ax.axis("off")


# ====================================================================
# 4. Static Background
# ====================================================================

# Wall
ax.plot(
    [WALL_X, WALL_X],
    [-1.0, 1.0],
    "k-",
    lw=3
)


# ====================================================================
# 5. Dynamic Objects
# ====================================================================

initial_x = POSITION_DATA[0]

# Mass
mass_x_start = initial_x - MASS_WIDTH / 2

mass_y_bottom = (
    (CENTER_Y_SPRING + CENTER_Y_DAMPER) / 2
    - MASS_HEIGHT / 2
)

mass_rect = patches.Rectangle(
    (mass_x_start, mass_y_bottom),
    MASS_WIDTH,
    MASS_HEIGHT,
    fc="blue",
    ec="black",
    zorder=5
)

ax.add_patch(mass_rect)


# Ground / Rail
ax.plot(
    [WALL_X, ax.get_xlim()[1]],
    [mass_y_bottom, mass_y_bottom],
    "k-",
    lw=2
)


# Spring
spring_x_coords, spring_y_coords = create_spring_shape(
    WALL_X,
    mass_x_start,
    CENTER_Y_SPRING
)

spring_line, = ax.plot(
    spring_x_coords,
    spring_y_coords,
    "g-",
    lw=2,
    zorder=3
)


# Damper rod
damper_rod, = ax.plot(
    [mass_x_start, WALL_X],
    [CENTER_Y_DAMPER, CENTER_Y_DAMPER],
    "k-",
    lw=2,
    zorder=4
)


# Piston
piston_x_start = (
    mass_x_start + WALL_X - PISTON_WIDTH
) / 2

piston_y_bottom = CENTER_Y_DAMPER - PISTON_HEIGHT / 2

piston_rect = patches.Rectangle(
    (piston_x_start, piston_y_bottom),
    PISTON_WIDTH,
    PISTON_HEIGHT,
    fc="black",
    ec="k",
    zorder=4
)

ax.add_patch(piston_rect)


# Display information
time_text = ax.text(
    0.05, 0.95, "",
    transform=ax.transAxes,
    fontsize=12,
    va="top"
)

pos_text = ax.text(
    0.05, 0.85, "",
    transform=ax.transAxes,
    fontsize=12,
    va="top"
)

method_text = ax.text(
    0.05, 0.75, f"Method: {METHOD}",
    transform=ax.transAxes,
    fontsize=12,
    va="top"
)


# ====================================================================
# 6. Animation Update Function
# ====================================================================

def update(frame):

    current_time = TIME_DATA[frame]
    current_x_mass_center = POSITION_DATA[frame]

    mass_x_start = current_x_mass_center - MASS_WIDTH / 2

    # Update mass
    mass_rect.set_x(mass_x_start)

    # Update spring
    spring_x_coords, spring_y_coords = create_spring_shape(
        WALL_X,
        mass_x_start,
        CENTER_Y_SPRING
    )

    spring_line.set_xdata(spring_x_coords)
    spring_line.set_ydata(spring_y_coords)

    # Update damper rod
    damper_rod.set_xdata([
        mass_x_start,
        WALL_X
    ])

    # Update piston
    piston_x_start = (
        mass_x_start + WALL_X - PISTON_WIDTH
    ) / 2

    piston_rect.set_x(piston_x_start)

    # Update text
    time_text.set_text(f"Time: {current_time:.2f} s")

    pos_text.set_text(
        f"Position: {current_x_mass_center:.3f} m"
    )

    return (
        mass_rect,
        spring_line,
        damper_rod,
        piston_rect,
        time_text,
        pos_text,
        method_text
    )


# ====================================================================
# 7. Start Animation
# ====================================================================

ani = FuncAnimation(
    fig,
    update,
    frames=len(POSITION_DATA),
    interval=INTERVAL_MS,
    blit=True,
    repeat=False
)

plt.show()
