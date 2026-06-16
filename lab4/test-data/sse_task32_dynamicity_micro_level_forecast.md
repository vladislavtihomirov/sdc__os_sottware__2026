# SSE Task 32: Dynamicity and Micro-Level Forecast

## Selected key component

**Component:** Sorting and conveyor control module in the airport luggage tracking and handling system.

---

## Current state on the dynamicity line

**Current state:** Flexible

The sorting and conveyor control module can already change bag routes and control different conveyor zones, but it still depends on fixed rules, fixed scanner points, and predefined conveyor paths.

---

## Previous state

**Previous state:** Jointed

Earlier baggage systems used more mechanical and semi-manual sorting. Conveyor sections and diverters worked separately, and staff had more direct control over exception handling.

---

## Possible next states

1. **Field-based / adaptive control**  
   The system dynamically changes conveyor speed, routing, and spacing using real-time sensor data.

2. **Microservice-based routing system**  
   Routing, scanning, congestion detection, exception handling, and notifications are separated into smaller software services.

3. **Agent-based luggage control**  
   Each bag has a digital agent that tracks its route, priority, transfer time, and loading status.

---

## Transition to the micro-level

A transition to the micro-level is possible.

Possible micro-level directions:

- **Smaller modules:** separate control for each conveyor zone.
- **Microservices:** independent services for scanning, routing, congestion prediction, and alerts.
- **Functions / agents:** each bag is represented by a digital tracking agent.
- **Algorithmic mechanism:** AI or rule-based system predicts congestion and misrouting risks.
- **Field-based mechanism:** sensors continuously control speed, spacing, and routing.

---

## Problem solved by the next state

The next state may solve the problem of **silent baggage misrouting and conveyor congestion**.

Instead of reacting after the bag is already delayed or misplaced, the system can detect risk earlier and automatically adjust speed, route, or priority.

---

## New risk or contradiction

A new contradiction may appear:

The system becomes more adaptive and accurate, but also more complex and harder to control.

**New risk:** If microservices, sensors, or bag agents fail to synchronize, the system may make conflicting routing decisions or send incorrect status updates.
