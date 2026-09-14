# Bug Analysis Report

| Bug Number | Problem | Root Cause | Resolution |
| --- | --- | --- | --- |
| 1 | Total revenue was too low. | `calculateRevenue()` added only `ticketPrice`, ignoring the number of tickets. | Calculate `tickets * ticketPrice` for every booking before summing. |
| 2 | Every booking was returned as an attendee and source data was changed. | `getAttendees()` used assignment (`booking.attended = true`) inside `filter()`. | Use a strict comparison: `booking.attended === true`. |
| 3 | Popular event totals were not calculated. | `eventMap[booking.eventName]` started as `undefined`, so adding tickets produced `NaN`. | Initialize missing event totals to `0` before adding tickets. |
| 4 | The original popular-event function returned the complete map instead of the event name. | It aggregated values but did not select the event with the greatest ticket total. | Aggregate ticket totals and reduce the entries to the event with the highest total, preserving the first tie. |
| 5 | Repeated analytics logic could drift between reports. | Revenue, attendance, and customer calculations were not separated into reusable operations. | Add focused report functions and compose `generateDashboard()` from them. |
