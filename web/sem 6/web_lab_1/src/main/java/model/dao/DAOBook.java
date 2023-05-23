package model.dao;

import model.DBConnectionException;
import model.DaoException;
import model.entity.Book;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;


public class DAOBook extends DAO {
    private static final String SELECT_ALL_BOOKS_SQL = "select * from books";
    private static final String DELETE_ITEM_BOOK_SQL = "update books set number_of_instances = number_of_instances - 1 where id_books = ?";
    private static final String ADD_ITEM_BOOK_SQL = "update books set number_of_instances = number_of_instances + 1 where id_books = ?";
    private static final String SELECT_BOOKS_BY_AUTHOR_SQL = "select * from books where author = ?";
    private static final String SELECT_INSTANCES_BY_ID_SQL = "select count(*) from books where id_books = ?";

    public DAOBook() throws DaoException {
        super();
    }

    public void removeItemBook(int id) throws DaoException{
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(DELETE_ITEM_BOOK_SQL);
            stmt.setInt(1, id);
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new DaoException("Remove item book exception ", e);
        } catch (DBConnectionException e) {
            throw new DaoException("Failed to get connection from db connector ", e);
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

    public void addItemBook(int id) throws DaoException{
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(ADD_ITEM_BOOK_SQL);
            stmt.setInt(1, id);
            stmt.executeUpdate();
        } catch (SQLException e) {
            throw new DaoException("Add item book exception ", e);
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

    public List getBooks(String author) throws DaoException {
        ArrayList<Book> books = new ArrayList<Book>();
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(SELECT_BOOKS_BY_AUTHOR_SQL);
            stmt.setString(1, author);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                int id = rs.getInt(1);
                String name = rs.getString(2);
                int num = rs.getInt(4);
                books.add(new Book(id, name, author, num));
            }
        } catch (SQLException e) {
            throw new DaoException("Get all books exception ", e);
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
        return books;
    }

    public List getAll() throws DaoException {
        ArrayList<Book> books = new ArrayList<Book>();
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(SELECT_ALL_BOOKS_SQL);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                int id = rs.getInt(1);
                String title = rs.getString(2);
                String author = rs.getString(3);
                int num = rs.getInt(4);
                books.add(new Book(id, title, author, num));
            }
        } catch (SQLException e) {
            throw new DaoException("Get all books exception ", e);
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
        return books;
    }

    public int getInstances(int id_books) throws DaoException {
        int inst = -1;
        Connection connection = null;
        try {
            connection = getDBConnector().getConnection();
            PreparedStatement stmt = connection.prepareStatement(SELECT_INSTANCES_BY_ID_SQL);
            stmt.setInt(1, id_books);
            ResultSet rs = stmt.executeQuery();
            while (rs.next()) {
                int id = rs.getInt(1);
                String name = rs.getString(2);
                inst = rs.getInt(4);
            }
        } catch (SQLException e) {
            throw new DaoException("Get all books exception ", e);
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
        return inst;
    }
}