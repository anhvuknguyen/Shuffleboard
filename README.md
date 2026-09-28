# Shuffleboard

A two-player shuffleboard game for the TI MSPM0 LaunchPad, with a hand-written 2D physics engine, real-time audio playback, and a custom PCB for the input hardware.

Built as the final project for EE 319K (Introduction to Embedded Systems) at UT Austin.

**[▶ Demo video](https://youtu.be/GUb15umj7tY)**

![Gameplay](docs/gameplay.gif)

---

## How it plays

Each player gets three pucks. You set your launch position with a slide potentiometer, aim with a joystick, and fire with a button. An on-screen arrow shows your aim in real time — its direction and length track the joystick, so the length doubles as a power indicator.

Once a puck is launched it slides, decelerates under friction, and collides with any pucks already on the board. When everything comes to rest, each puck is scored by the region its center is sitting on.

---

## Architecture

The system runs two interrupts at different rates, doing very different work.

### 30 Hz timer ISR (TIMG12) — simulation and rendering

Drives the game at 30 FPS. Each tick:

- Samples the joystick and slide pot from the external ADC over I²C
- Updates the aiming arrow's length and direction
- Integrates puck positions, applies friction, and resolves collisions
- Redraws the board

### 7 kHz SysTick ISR — audio

Streams PCM samples to the MSPM0's internal DAC one sample per tick. Sound effects were converted from WAV files into C arrays at build time, so playback is just walking an array and writing the DAC at a fixed rate.

### Why the two don't fight

The audio ISR fires roughly 233 times per physics frame, so anything slow inside the 30 Hz ISR risks starving it. The I²C reads are the slow part — a config write plus a conversion read on the ADS1115 is on the order of a millisecond.

That never becomes a problem, because the game's state machine keeps the two workloads disjoint:

| State | I²C sampling | Audio |
|---|---|---|
| Aiming | Yes | Idle |
| Puck motion / collision | No | Playing |
| Victory screen | No | Playing |

You can't aim while pucks are moving, and you can't shoot until every puck has come to rest. So the expensive input path and the expensive audio path are never live in the same frame.

---

## Physics

Pucks are modeled as circles with position, velocity, and a friction coefficient applied per frame. Collisions are detected by center-distance against the sum of the radii, and resolved elastically along the line connecting the two centers.

Scoring samples the board region underneath each puck's center once its velocity reaches zero, and adds the point value for that region's color.

---

## Hardware

Input devices live on a custom PCB designed in KiCad:

- **ADS1115** 16-bit external ADC, read over I²C — two single-ended channels for the joystick axis and the slide potentiometer
- **RC low-pass filters** on the fire and reset buttons for hardware debouncing, rather than handling bounce in software
- **Bulk decoupling capacitors** at the supply rails, to keep the rail from dipping below the MCU's minimum when the circuit draws current in bursts

---

## Building

Open the project in Code Composer Studio, select the MSPM0 LaunchPad target, and flash.

```
software/   game logic, physics, ISRs, PCM sample arrays generated from WAV files
hardware/   KiCad schematic and board files
```

---
