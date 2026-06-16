# SSE Task 34: System-Level Evolution Forecast

## Selected system

**Airport luggage tracking and handling system**

---

## Current evolution mode

**Current mode:** Transition to super-system

The airport luggage system is no longer only a separate baggage-handling mechanism. It is becoming part of a larger airport digital ecosystem that includes airline systems, flight schedules, passenger notifications, security systems, and airport operations dashboards.

---

## Lagging subsystem

**Lagging subsystem:** Real-time route verification and prediction

This subsystem limits further development because the system can scan, sort, and track bags, but it does not always predict or detect misrouting early enough.

The weak point is the connection between:

- scanner data,
- routing database,
- conveyor position,
- sorting decision,
- loading confirmation.

---

## Transformation 1: Digital twin of baggage flow

The system may evolve into a **digital twin** that shows the real-time position and expected route of each bag.

**Useful effect:**  
Operators can detect misrouting, congestion, and delays before the bag reaches the wrong aircraft loading area.

**Contradiction / risk:**  
The system becomes more controllable, but also more complex. If sensor data is missing or delayed, the digital twin may show an incorrect picture of reality.

---

## Transformation 2: Agent-based baggage control

Each bag may receive a digital agent that manages its route, priority, transfer status, and loading confirmation.

**Useful effect:**  
The system can make more individual decisions for each bag, especially for transfer bags, delayed bags, and priority luggage.

**Contradiction / risk:**  
The system becomes more adaptive, but coordination between many bag agents may create conflicts, overload the control software, or generate inconsistent routing decisions.
