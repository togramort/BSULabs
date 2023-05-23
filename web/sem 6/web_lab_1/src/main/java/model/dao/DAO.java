package model.dao;

import model.ConnectionPool;
import model.DBConnectionException;
import model.DaoException;

public class DAO {
    private final ConnectionPool dbc;

    public DAO() throws DaoException {
        try {
            dbc = ConnectionPool.getInstance();
        } catch (DBConnectionException e) {
            throw new DaoException("Cannot create DBConnectionPool ", e);
        }
    }

    protected ConnectionPool getDBConnector() {
        return dbc;
    }
}
