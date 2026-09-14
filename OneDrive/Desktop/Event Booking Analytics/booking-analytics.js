const bookings = [
  {
    bookingId: 1,
    customerName: "Rahul",
    eventName: "Angular Summit",
    tickets: 2,
    ticketPrice: 500,
    attended: true
  },
  {
    bookingId: 2,
    customerName: "Priya",
    eventName: "NodeJS Bootcamp",
    tickets: 1,
    ticketPrice: 700,
    attended: false
  },
  {
    bookingId: 3,
    customerName: "Arun",
    eventName: "Angular Summit",
    tickets: 3,
    ticketPrice: 500,
    attended: true
  },
  {
    bookingId: 4,
    customerName: "Divya",
    eventName: "React Conference",
    tickets: 4,
    ticketPrice: 600,
    attended: true
  }
];

function calculateRevenue(bookingList) {
  return bookingList.reduce(
    (total, booking) => total + booking.tickets * booking.ticketPrice,
    0
  );
}

function getAttendees(bookingList) {
  return bookingList.filter(booking => booking.attended === true);
}

function getEventRevenueMap(bookingList) {
  return bookingList.reduce((eventMap, booking) => {
    eventMap[booking.eventName] =
      (eventMap[booking.eventName] || 0) + booking.tickets * booking.ticketPrice;
    return eventMap;
  }, {});
}

function getPopularEvent(bookingList) {
  const ticketTotals = bookingList.reduce((eventMap, booking) => {
    eventMap[booking.eventName] =
      (eventMap[booking.eventName] || 0) + booking.tickets;
    return eventMap;
  }, {});

  return Object.entries(ticketTotals).reduce(
    (popularEvent, [eventName, tickets]) =>
      tickets > popularEvent.tickets
        ? { eventName, tickets }
        : popularEvent,
    { eventName: null, tickets: 0 }
  ).eventName;
}

function generateRevenueReport(bookingList) {
  return getEventRevenueMap(bookingList);
}

function getTopRevenueEvent(bookingList) {
  const revenueMap = generateRevenueReport(bookingList);

  return Object.entries(revenueMap).reduce(
    (topEvent, [eventName, revenue]) =>
      revenue > topEvent.revenue ? { eventName, revenue } : topEvent,
    { eventName: null, revenue: 0 }
  );
}

function generateAttendanceReport(bookingList) {
  const totalBookings = bookingList.length;
  const totalAttendees = getAttendees(bookingList).length;
  const attendancePercentage = totalBookings === 0
    ? 0
    : Number(((totalAttendees / totalBookings) * 100).toFixed(2));

  return {
    totalBookings,
    totalAttendees,
    attendancePercentage
  };
}

function generateCustomerSpendingReport(bookingList) {
  return bookingList.reduce((spending, booking) => {
    spending[booking.customerName] = booking.tickets * booking.ticketPrice;
    return spending;
  }, {});
}

function generateVipCustomers(bookingList) {
  return Object.entries(generateCustomerSpendingReport(bookingList))
    .filter(([, spending]) => spending >= 1500)
    .map(([customerName]) => customerName);
}

function validateBooking(booking) {
  const errors = [];

  if (typeof booking.customerName !== "string" || booking.customerName.trim() === "") {
    errors.push("Customer Name Required");
  }
  if (!Number.isInteger(booking.tickets) || booking.tickets <= 0) {
    errors.push("Invalid Ticket Count");
  }
  if (typeof booking.ticketPrice !== "number" || booking.ticketPrice <= 0) {
    errors.push("Ticket Price Required");
  }

  return {
    isValid: errors.length === 0,
    errors
  };
}

function generateDashboard(bookingList) {
  const attendance = generateAttendanceReport(bookingList);

  return {
    totalRevenue: calculateRevenue(bookingList),
    totalBookings: attendance.totalBookings,
    totalAttendees: attendance.totalAttendees,
    attendancePercentage: attendance.attendancePercentage,
    topRevenueEvent: getTopRevenueEvent(bookingList).eventName,
    vipCustomers: generateVipCustomers(bookingList)
  };
}

if (require.main === module) {
  const invalidBooking = {
    bookingId: 10,
    customerName: "",
    tickets: -2,
    ticketPrice: null
  };

  console.log("Revenue Report:", generateRevenueReport(bookings));
  console.log("Top Revenue Event:", getTopRevenueEvent(bookings));
  console.log("Attendance Report:", generateAttendanceReport(bookings));
  console.log("Customer Spending Report:", generateCustomerSpendingReport(bookings));
  console.log("VIP Customers:", generateVipCustomers(bookings));
  console.log("Dashboard:", generateDashboard(bookings));
  console.log("Validation Output:", validateBooking(invalidBooking));
}

module.exports = {
  bookings,
  calculateRevenue,
  getAttendees,
  getPopularEvent,
  generateRevenueReport,
  getTopRevenueEvent,
  generateAttendanceReport,
  generateCustomerSpendingReport,
  generateVipCustomers,
  validateBooking,
  generateDashboard
};
