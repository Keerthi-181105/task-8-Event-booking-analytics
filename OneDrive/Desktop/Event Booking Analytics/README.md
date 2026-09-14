# Event Booking Analytics Engine

## Project Overview

A Node.js analytics engine for EventSphere bookings. It fixes the supplied booking-summary bugs and generates reusable revenue, attendance, customer-spending, VIP, validation, and dashboard reports.

## Features Implemented

- Event revenue report using `tickets * ticketPrice`
- Top revenue event with first-encountered tie handling
- Popular event by total tickets sold
- Attendance count and percentage rounded to two decimal places
- Customer spending report
- VIP customer report for spending of at least 1500
- Full booking validation with all errors returned
- Composite analytics dashboard object
- Reusable functions with no duplicated business calculations

## Bugs Fixed

See [BUG-ANALYSIS.md](BUG-ANALYSIS.md) for the problem, root cause, and resolution for each defect in the original implementation.

## How To Execute

Requires Node.js 14 or newer.

The assignment output is displayed in the terminal. No HTML file is required.

```bash
node booking-analytics.js
```

To use the functions from another script:

```js
const analytics = require('./booking-analytics');
const dashboard = analytics.generateDashboard(analytics.bookings);
```

## Sample Output

```text
Revenue Report: {
  'Angular Summit': 2500,
  'NodeJS Bootcamp': 700,
  'React Conference': 2400
}
Top Revenue Event: { eventName: 'Angular Summit', revenue: 2500 }
Attendance Report: { totalBookings: 4, totalAttendees: 3, attendancePercentage: 75 }
Customer Spending Report: { Rahul: 1000, Priya: 700, Arun: 1500, Divya: 2400 }
VIP Customers: [ 'Arun', 'Divya' ]
Dashboard: {
  totalRevenue: 5600,
  totalBookings: 4,
  totalAttendees: 3,
  attendancePercentage: 75,
  topRevenueEvent: 'Angular Summit',
  vipCustomers: [ 'Arun', 'Divya' ]
}
Validation Output: {
  isValid: false,
  errors: [
    'Customer Name Required',
    'Invalid Ticket Count',
    'Ticket Price Required'
  ]
}
```

## Screenshots

The individual PNG files document each requested output:

- [Revenue Report](screenshots/revenue-report.png)
- [Attendance Report](screenshots/attendance-report.png)
- [VIP Customers](screenshots/vip-customers.png)
- [Dashboard Output](screenshots/dashboard-output.png)
- [Validation Output](screenshots/validation-output.png)
