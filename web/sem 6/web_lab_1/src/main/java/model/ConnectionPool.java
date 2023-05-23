package model;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.SQLTimeoutException;
import java.util.ResourceBundle;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

public class ConnectionPool {
    private static ConnectionPool instance;
    private static final int initConnectionsCount = 5;
    private BlockingQueue<Connection> connections;

    private static String URL;
    private static String USER;
    private static String PASS;

    private ConnectionPool() throws DBConnectionException {
        if (instance != null)
            return;
        ResourceBundle resource = ResourceBundle.getBundle("database");

        String DRIVER = resource.getString("driver");
        URL = resource.getString("url");
        USER = resource.getString("user");
        PASS = resource.getString("password");

        try {
            Class.forName(DRIVER);
        } catch (ClassNotFoundException e) {
            throw new DBConnectionException("Error loading driver!", e);
        }

        connections = new ArrayBlockingQueue<>(initConnectionsCount);
        try {
            for (int i = 0; i < initConnectionsCount; i++) {
                Connection connection = DriverManager.getConnection(URL, USER, PASS);
                if (connection == null) {
                    throw new DBConnectionException("Driver type is not correct in URL " + URL + ".");
                }
                connections.add(connection);
            }
        } catch (SQLTimeoutException e){
            throw new DBConnectionException("Failed to authorize", e);
        } catch (SQLException e) {
            throw new DBConnectionException("Failed to establish connection", e);
        }
    }

    public static synchronized ConnectionPool getInstance() throws DBConnectionException {
        if (instance == null) {
            instance = new ConnectionPool();
        }

        return instance;
    }

    public synchronized Connection getConnection() throws DBConnectionException {
        try {
            return connections.take();
        } catch (InterruptedException e) {
            throw new DBConnectionException("Failed to get connection from pool", e);
        }
    }

    public synchronized void releaseConnection(Connection connection) throws DBConnectionException {
        try {
            if (connection.isClosed()) {
                Connection newConnection = DriverManager.getConnection(URL, USER, PASS);
                connections.add(newConnection);
            } else {
                connections.add(connection);
            }
        } catch (SQLException e) {
            throw new DBConnectionException("Failed to establish connection", e);
        }

    }
}