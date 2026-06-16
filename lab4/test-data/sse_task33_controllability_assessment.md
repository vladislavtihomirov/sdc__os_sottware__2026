# SSE Task 33: Controllability Assessment

## Selected system

**Airport luggage tracking and handling system**

---

## How the operator receives information now

Operators and staff receive information through:

- Scanner indicators
- Baggage handling dashboards
- Conveyor status monitoring
- Security screening alerts
- System logs
- Manual reports from baggage staff
- Passenger complaints or service desk reports
- Loading confirmation records

---

## Existing information channels

- **Sensors:** bag position sensors, conveyor sensors, scanner checkpoints
- **System logs:** scan events, routing decisions, error logs
- **Telemetry:** conveyor speed, jam alerts, system status
- **Dashboards:** baggage flow, exceptions, loading status
- **Manual reports:** staff reports about damaged, delayed, or suspicious bags
- **External data sources:** flight schedule, gate changes, transfer information
- **User feedback:** passenger reports about missing or delayed luggage

---

## Existing or missing information model

The system currently has mainly a **descriptive and operational model**.

It can show what happened: bag scanned, bag routed, bag loaded, or bag delayed.

However, it lacks a strong **predictive model** and a complete **digital model / digital twin**.

Missing models:

- Predictive model for congestion and jams
- Predictive model for misrouting risk
- Digital model of the real-time bag path
- Decision-support model for exception handling
- Feedback model connecting passenger complaints with system errors

---

## Next step to increase controllability

The next step is to create a **real-time route and congestion monitoring model**.

This model should:

- Compare expected bag route with actual route
- Detect delays before bags miss flights
- Predict congestion near scanners, diverters, and loading areas
- Alert operators when bags enter the wrong zone
- Recommend automatic speed reduction or rerouting

---

## Diagnostic

The most important hidden state is whether each bag is still moving on its **correct route in real time**.

To control it better, the system needs a **real-time digital route model** that connects scan data, conveyor position, routing database, and loading confirmation.
