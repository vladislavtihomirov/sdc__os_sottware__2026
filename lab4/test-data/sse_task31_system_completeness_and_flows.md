# SSE Task 31: System Completeness and Flows

## Selected system

**Airport luggage tracking and handling system**

## System completeness and flows

| System | Main function | Mandatory parts | Flows | Weak / missing elements |
|---|---|---|---|---|
| Airport luggage tracking and handling system | Move passenger luggage from bag drop to the correct aircraft safely, quickly, and accurately | **Object / processed object:** passenger checked bag<br><br>**Working organ:** conveyor belts, scanners, sorting diverters, loading equipment<br><br>**Resources / energy source:** electric power, barcode/RFID data, flight schedule data, staff actions<br><br>**Transmission / mechanism:** conveyor belt movement, diverter mechanism, scanner-to-database communication<br><br>**Control unit:** baggage handling software, routing database, sensors, monitoring system | **Material flow:** bag moves from bag drop → conveyor → screening → sorting → loading area → aircraft<br><br>**Energy flow:** electric power drives conveyors, scanners, diverters, and loading devices<br><br>**Information flow:** bag tag data, scan results, routing data, screening status, loading confirmation | **Weak:** bag tag readability, scanner reliability, conveyor spacing control<br><br>**Overloaded:** conveyor during peak baggage flow, manual inspection during false alarms<br><br>**Delayed:** routing updates, passenger notifications, exception handling<br><br>**Distorted:** incorrect routing data or outdated flight/transfer information<br><br>**Missing:** automatic route-verification checkpoint after sorting |

---

## Diagnostic

The most critical weak flow is the **information flow** between the scanner, routing database, and sorting system.  
If this flow is delayed, distorted, or missing, the system may send bags to the wrong conveyor path or aircraft.

The most important missing element is an **automatic route-verification checkpoint after sorting**.
