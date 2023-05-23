package model;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.ResourceBundle;

public class JdbcConnector {
    private Connection conn;

    public Connection getConn() throws JDBCConnectionException {
        ResourceBundle resource = ResourceBundle.getBundle("database");

        String driver = resource.getString("driver");
        String url = resource.getString("url");
        String user = resource.getString("user");
        String pass = resource.getString("password");

        try {
            Class.forName(driver).newInstance();
        } catch (ClassNotFoundException e) {
            throw new JDBCConnectionException ("Driver not loaded!");
        } catch (InstantiationException | IllegalAccessException e) {
            throw new JDBCConnectionException("Can't access database!");
        }

        try {
            conn = DriverManager.getConnection(url, user, pass);
        } catch (SQLException e) {
            throw new JDBCConnectionException("Can't get connection!");
        }
        return conn;
    }

    public void close() throws JDBCConnectionException {
        if (conn != null) {
            try {
                conn.close();
            } catch (SQLException e) {
                throw new JDBCConnectionException("Can't close connection", e);
            }
        }
    }
}