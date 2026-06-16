# SSE Task 35: Evolution Forecast Canvas

## Selected system

**Airport luggage tracking and handling system**

---

## Main function of the system

The main function of the system is to **move passenger luggage from bag drop to the correct aircraft safely, quickly, and accurately**.

---

## Current limitation

**Current limitation:** Development bottleneck

The system can scan, sort, and transport luggage, but it does not always detect misrouting, congestion, or delayed bags early enough.

The main bottleneck is weak **real-time route verification and prediction**.

---

## Selected evolution law / line

**Selected evolution line:** Increasing controllability

This line is the most relevant because the system needs better visibility and control over bag location, routing accuracy, conveyor congestion, and loading status.

---

## Current position on the evolution line

**Current position:** Descriptive / operational control

The system can show events such as scanned bag, routed bag, delayed bag, or loaded bag.  
However, it mostly reacts after the event has happened.

---

## Next possible state

**Next state:** Predictive and adaptive control

The system can predict congestion, detect wrong routing earlier, and automatically adjust conveyor speed, spacing, or bag route.

Possible features:

- Real-time route verification
- Predictive congestion detection
- Automatic rerouting
- Digital model of each bag path
- Early alerts before missed loading

---

## Contradiction created by the transition

The system becomes more controllable and predictive, but also more complex.

**Contradiction:**  
The system must use more data, sensors, and algorithms to improve control, but this can increase complexity, synchronization problems, and the risk of wrong automated decisions.

---

## Solution direction

Create a **real-time baggage digital twin with decision support**.

The system should:

- Compare expected and actual bag routes
- Detect route deviations early
- Predict congestion near scanners, diverters, and loading areas
- Recommend or automatically apply speed reduction and rerouting
- Keep human operators in control for critical decisions
