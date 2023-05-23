package model.dao;

import model.DBConnectionException;
import model.DaoException;
import model.entity.Reader;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.sql.Date;
import java.util.List;

public class DAOReader extends DAO {
    private static final String SELECT_ALL_READERS_SQL = "select * from reader";
    private static final String SELECT_READER_BY_ID_SQL = "select * from reader where id = ?";

    public DAOReader() throws DaoException {
        super();
    }

    public Reader get(int id) throws DaoException {
        Reader reader = null;
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(SELECT_READER_BY_ID_SQL);
            stmt.setInt(1, id);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                String name = rs.getString(2);
                Date birth = rs.getDate(3);
                reader = new Reader(id, name, birth);
            }
        } catch (SQLException e) {
            throw new DaoException("Get reader exception ", e);
        } catch (DBConnectionException e) {
            throw new DaoException("Faild to get connection from db connector ", e);
        } finally {
            if (connection != null) {
                try {
                    getDBConnector().releaseConnection(connection);
                } catch (DBConnectionException e) {
                    throw new DaoException("Failed to return connection to db connector ", e);
                }
            }
        }
        return reader;
    }

    public List getAll() throws DaoException {
        ArrayList<Reader> readers = new ArrayList<Reader>();
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(SELECT_ALL_READERS_SQL);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                int id = rs.getInt(1);
                String name = rs.getString(2);
                Date birth = rs.getDate(3);
                Reader reader = new Reader(id, name, birth);
                readers.add(reader);
            }
        } catch (SQLException e) {
            throw new DaoException("Get all readers exception ", e);
        } catch (DBConnectionException e) {
            throw new DaoException("Failed to get connection from connector", e);
        } finally {
            if (connection != null) {
                try {
                    getDBConnector().releaseConnection(connection);
                } catch (DBConnectionException e) {
                    throw new DaoException("Failed to return connection to db connector ", e);
                }
            }
        }
        return readers;
    }
}