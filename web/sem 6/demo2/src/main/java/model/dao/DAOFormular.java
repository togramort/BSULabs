package model.dao;

import model.entity.*;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.criteria.*;
import java.util.List;

public class DAOFormular extends DAO {

    public DAOFormular(){
        super();
    }

    public void delete(int book_id, int reader_id) {
        EntityTransaction transaction = null;
        EntityManager entityManager = null;

        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            transaction = entityManager.getTransaction();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaDelete<Formular> cq = cb.createCriteriaDelete(Formular.class);
            Root<Formular> formularRoot = cq.from(Formular.class);
            cq.where(cb.and(
                    cb.equal(formularRoot.get(Formular_.book), book_id)),
                    cb.equal(formularRoot.get(Formular_.reader), reader_id)
            );
            transaction.begin();
            entityManager.createQuery(cq).executeUpdate();
            transaction.commit();
        } catch (Exception e) {
            e.printStackTrace();
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }

    public void save(Formular l) {
        EntityTransaction transaction = null;
        EntityManager entityManager = null;

        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            transaction = entityManager.getTransaction();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaUpdate<Formular> cq = cb.createCriteriaUpdate(Formular.class);
            Root<Formular> formularRoot = cq.from(Formular.class);
            cq.set(Formular_.start_day, cb.currentDate())
                    .where(cb.equal(formularRoot.get(Formular_.book), l.getId()));
            transaction.begin();
            entityManager.createQuery(cq).executeUpdate();
            transaction.commit();
        } catch (Exception e) {
            e.printStackTrace();
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
        } finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }

    public List<Formular> getDebtors() {
        EntityManager entityManager = null;
        List<Formular> formularList;

        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Formular> cq = cb.createQuery(Formular.class);
            Root<Formular> readerRoot = cq.from(Formular.class);
            cq.where(cb.greaterThan(readerRoot.get(Formular_.return_day), readerRoot.get(Formular_.end_day)));
            formularList = entityManager.createQuery(cq).getResultList();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return formularList;
    }

    public List<Formular> getAll() {
        EntityManager entityManager = null;
        List<Formular> formularList;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Formular> cq = cb.createQuery(Formular.class);
            Root<Formular> formularRoot = cq.from(Formular.class);
            cq.select(formularRoot);
            formularList = entityManager.createQuery(cq).getResultList();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return formularList;
    }
}