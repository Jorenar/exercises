CREATE TABLE clients (
    id      INTEGER PRIMARY KEY AUTOINCREMENT,
    name    TEXT,
    surname TEXT,
    tel     TEXT,
    email   TEXT
);

CREATE TABLE devices (
    id   INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT,
    type TEXT
);

CREATE TABLE devices_owners (
    deviceID INTEGER,
    ownerIDi  INTEGER,
    FOREIGN KEY (deviceID) REFERENCES devices(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (ownerID)  REFERENCES clients(id) ON DELETE CASCADE ON UPDATE CASCADE,
    PRIMARY KEY (deviceID, ownerID)
);

CREATE TABLE orders (
    id        INTEGER PRIMARY KEY AUTOINCREMENT,
    deviceID  INTEGER,
    clientID  INTEGER,
    inDate    INTEGER,
    outDate   INTEGER,
    state     TEXT,
    FOREIGN KEY (deviceID) REFERENCES devices(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (clientID) REFERENCES clients(id) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE ordered_services (
    orderID     INTEGER,
    serviceID   INTEGER,
    price       REAL,
    startDate   INTEGER,
    endDate     INTEGER,
    description TEXT,
    FOREIGN KEY (id)        REFERENCES orders(id)   ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (serviceID) REFERENCES services(id) ON DELETE CASCADE ON UPDATE CASCADE,
    PRIMARY KEY (orderID, serviceID)
);

CREATE TABLE services (
    id    INTEGER PRIMARY KEY AUTOINCREMENT,
    name  TEXT,
    price REAL
);


CREATE TABLE parts (
    id       INTEGER PRIMARY KEY AUTOINCREMENT,
    name     TEXT,
    quantity INTEGER
);

CREATE TABLE tools (
    id       INTEGER PRIMARY KEY AUTOINCREMENT,
    name     TEXT,
    type     TEXT,
    quantity INTEGER
);

CREATE TABLE accessories (
    id       INTEGER PRIMARY KEY AUTOINCREMENT,
    name     TEXT,
    type     TEXT,
    quantity INTEGER
);

CREATE TABLE tools_accessories (
    toolID      INTEGER,
    accessoryID INTEGER,
    FOREIGN KEY (toolID)      REFERENCES tools(id) ON DELETE CASCADE ON UPDATE CASCADE,
    FOREIGN KEY (accessoryID) REFERENCES accessories(id) ON DELETE CASCADE ON UPDATE CASCADE,
    PRIMARY KEY (toolID, accessoryID)
);

CREATE TABLE substances (
    id       INTEGER PRIMARY KEY AUTOINCREMENT,
    name     TEXT,
    type     TEXT,
    quantity INTEGER,
    unit     TEXT
);


CREATE VIEW clients_view AS
SELECT clients.*, COUNT(orders.clientID) FROM clients
LEFT JOIN orders ON clients.id = orders.clientID
GROUP BY clients.id;

CREATE VIEW orders_view AS
SELECT
    id,
    deviceID,
    clientID,
    datetime(inDate,  'unixepoch'),
    datetime(outDate, 'unixepoch'),
    state
FROM clients;
