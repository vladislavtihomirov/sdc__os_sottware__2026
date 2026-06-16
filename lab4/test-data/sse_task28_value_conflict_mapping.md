# SSE Task 28: Value-Conflict Mapping

## Selected application

**Application:** Airport Luggage Tracking and Handling Application

The application supports baggage registration, scanning, routing, conveyor control, exception handling, aircraft loading confirmation, and passenger notifications.

---

## Value-Conflict Analysis

| Stakeholder requirement | Design component | Property | Value | Opposite value | Stakeholder requirement implemented by opposite value |
|---|---|---|---|---|---|
| Airport operator needs fast baggage processing | Conveyor control module | Conveyor speed | High speed | Low / controlled speed | Baggage handling staff need safer flow with fewer jams and collisions |
| Airline needs bags loaded onto the correct aircraft | Sorting module | Routing automation level | Fully automatic | Manual / semi-automatic | Staff need more control for exception bags and special cases |
| Passenger needs real-time baggage status | Notification module | Notification frequency | Immediate updates | Delayed / confirmed-only updates | Airline needs to avoid sending inaccurate or unconfirmed information |
| Security team needs dangerous items detected | Screening integration module | Detection sensitivity | High sensitivity | Lower sensitivity | Airport operator needs fewer false alarms and faster baggage flow |
| Baggage staff need clear exception handling | Exception management module | Exception detail level | Detailed alerts | Short simplified alerts | Staff need faster decision-making during peak workload |
| Airline needs accurate loading confirmation | Aircraft loading module | Confirmation method | Mandatory scan confirmation | Optional / automatic confirmation | Loading staff need faster loading with fewer manual scanning steps |
| Passenger needs easy bag identification | Bag registration module | Tag information amount | Detailed tag data | Minimal tag data | Airport needs tags that are simple, readable, and less error-prone |
| Airport operator needs high system efficiency | Conveyor entry control | Bag release interval | Short interval | Long interval | System needs better spacing to prevent congestion and misrouting |
| Airline needs flexible routing for transfer bags | Routing database | Route update frequency | Frequent updates | Stable fixed route | System needs routing stability to avoid wrong or outdated decisions |
| Passenger needs transparency about delays | Delay alert module | Alert threshold | Early alert | Late alert | Airline needs to avoid unnecessary concern when delay is not confirmed |
