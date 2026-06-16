# SSE Task 29: Hidden Problem Detection

| Object | Hidden problem | Weak point | Reason it is hidden | Revealing action |
|---|---|---|---|---|
| Airport luggage tracking and handling system | Some bags may be silently misrouted before the problem becomes visible to staff or passengers | Sorting module + routing database + peak-time baggage flow | **Time:** the problem appears only later, when the bag does not arrive at the aircraft or destination. **Complexity:** many components interact, so the exact cause is hard to notice immediately. | Add an automatic checkpoint after sorting: compare expected route with actual conveyor path and send an early alert when the bag moves to the wrong zone. |

## Short explanation

The hidden problem is that a bag can be misrouted inside the system without immediate detection.  
It stays hidden because the system is complex and the negative result becomes visible only after a delay.

## Conclusion

The best revealing action is to add **early route-verification checkpoints** after sorting and before aircraft loading.
