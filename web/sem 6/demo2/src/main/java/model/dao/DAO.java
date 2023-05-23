package model.dao;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;

public class DAO {
    private static String PERSISTENCE_UNIT_NAME = "kotleta";
    private EntityManagerFactory factory;

    DAO() {
        factory = Persistence.createEntityManagerFactory(PERSISTENCE_UNIT_NAME);
    }

    protected EntityManagerFactory getEntityManagerFactory() {
        return factory;
    }
}