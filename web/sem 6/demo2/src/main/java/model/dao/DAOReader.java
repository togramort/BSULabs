package model.dao;

import model.entity.Reader;
import model.entity.Reader_;

import javax.persistence.EntityManager;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.Root;
import java.util.List;

public class DAOReader extends DAO {

    public DAOReader() {
        super();
    }

    public List<Reader> getAll() {
        EntityManager entityManager = null;
        List<Reader> readerList;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Reader> cq = cb.createQuery(Reader.class);
            Root<Reader> student = cq.from(Reader.class);
            cq.select(student);
            readerList = entityManager.createQuery(cq)
                    .getResultList();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return readerList;
    }

    public Reader get(int id) {
        EntityManager entityManager = null;
        Reader reader;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Reader> readerCriteriaQuery = cb.createQuery(Reader.class);
            Root<Reader> readerRoot = readerCriteriaQuery.from(Reader.class);
            readerCriteriaQuery.where(cb.equal(readerRoot.get(Reader_.id), id));
            reader = entityManager.createQuery(readerCriteriaQuery).getSingleResult();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return reader;
    }
}