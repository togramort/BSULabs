package model.dao;

import model.DBConnectionException;
import model.DaoException;
import model.entity.Formular;
import model.entity.Reader;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.sql.Date;
import java.util.List;

public class DAOFormular extends DAO {
    private static final String INSERT_RECORD_SQL = "insert into formular (books_id_books, reader_id_reader, start_date, end_date, return_date) values(?, ?, ?, ?, ?)";
    private static final String DELETE_RECORD_SQL = "delete from formular where books_id_book = ? and reader_id_reader = ?";
    private static final String SELECT_ALL_RECORDS_SQL = "select * from formular";
    private static final String SELECT_READERS_WITH_ARREARS_SQL = "select r.id_reader, r.name, r.birth_date from reader r left join formular l " +
            "on l.reader_id_reader = r.id_reader where l.return_date > l.end_date";

    public DAOFormular() throws DaoException {
        super();

    }

    public List getDebtors() throws DaoException {
        ArrayList<Reader> readers = new ArrayList<Reader>();
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(SELECT_READERS_WITH_ARREARS_SQL);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                int id = rs.getInt(1);
                String name = rs.getString(2);
                Date birth = rs.getDate(3);
                readers.add(new Reader(id, name, birth));
            }
        } catch (SQLException e) {
            throw new DaoException("Get all debtors exception ", e);
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

    public List getAll() throws DaoException {
        ArrayList<Formular> logs = new ArrayList<Formular>();
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(SELECT_ALL_RECORDS_SQL);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                int id = rs.getInt(1);
                int book_id = rs.getInt(2);
                int reader_id = rs.getInt(3);
                Date start_date = rs.getDate(4);
                Date end_date = rs.getDate(5);
                Date return_date = rs.getDate(6);
                Formular f = new Formular(book_id, reader_id, start_date, end_date, return_date);
                logs.add(f);
            }
        } catch (SQLException e) {
            throw new DaoException("Get all logbook records exception ", e);
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
        return logs;
    }

    public void save(Formular l) throws DaoException {
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(INSERT_RECORD_SQL);
            stmt.setInt(1, l.getBook());
            stmt.setInt(2, l.getReader());
            stmt.setDate(3, l.getStart_day());
            stmt.setDate(4, l.getEnd_day());
            stmt.setDate(5, l.getReturn_day());
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new DaoException("Insert logbook record exception ", e);
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
    }

    public void delete(Formular l) throws DaoException {
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(DELETE_RECORD_SQL);
            stmt.setInt(1, l.getBook());
            stmt.setInt(2, l.getReader());
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new DaoException("Delete logbook exception ", e);
        }  catch (DBConnectionException e) {
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
    }
}