# SSE Task 29: Hidden Problem Detection

## Object

**Airport luggage tracking and handling system**

## Hidden problem

Some bags may be silently misrouted inside the airport luggage system before the problem becomes visible to staff or passengers.

A bag can move to the wrong conveyor zone or aircraft loading area, but the system may not detect the mistake immediately.

## Weak point

The weak point appears where these three factors coincide:

- **Component:** Sorting module
- **Resource:** Routing database
- **Condition:** Peak-time baggage flow

During peak time, many bags move through the system at the same time. If the routing database contains outdated or incorrect data, the sorting module may send a bag to the wrong path.

## Reason the problem is hidden

The problem stays hidden mainly because of **time** and **complexity**.

First, the negative effect appears later. Staff may only notice the issue when the bag does not arrive at the aircraft or destination.

Second, the system is complex. Many components work together: scanners, database, conveyor belts, sorting modules, and manual staff. Because of this, it is difficult to see the exact cause immediately.

## Revealing action

Add an automatic checkpoint after the sorting stage.

This checkpoint should compare the bag’s expected route with its actual conveyor path. If the bag enters the wrong zone, the system should send an early alert before the bag reaches the wrong aircraft loading area.

## Final output

**Object:** Airport luggage tracking and handling system

**Hidden problem:** Some bags may be silently misrouted before the problem becomes visible.

**Weak point:** Sorting module + routing database + peak-time baggage flow.

**Reason it is hidden:** Time delay and system complexity.

**Revealing action:** Add early route-verification checkpoints after sorting.
