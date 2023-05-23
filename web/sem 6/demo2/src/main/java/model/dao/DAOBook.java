package model.dao;

import model.entity.Book;
import model.entity.Book_;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import javax.persistence.criteria.CriteriaBuilder;
import javax.persistence.criteria.CriteriaQuery;
import javax.persistence.criteria.CriteriaUpdate;
import javax.persistence.criteria.Root;
import java.util.List;

public class DAOBook extends DAO {

    public DAOBook(){
        super();
    }

    public int getInstances(int id) {

        EntityManager entityManager = null;
        int number_of_instance;
        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Book> cq = cb.createQuery(Book.class);
            Root<Book> bookRoot = cq.from(Book.class);
            cq.where(cb.equal(bookRoot.get(Book_.id), id));
            number_of_instance = entityManager.createQuery(cq).getSingleResult().getNumber_of_instance();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return number_of_instance;
    }

    public List<Book> getBooksByAuthor(String author) {
        EntityManager entityManager = null;
        List<Book> bookList;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            bookList = entityManager.createNamedQuery("getBooksByAuthor", Book.class)
                    .setParameter("author", author).getResultList();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return bookList;
    }

    public List<Book> getBooks(String author) {
        EntityManager entityManager = null;
        List<Book> bookList;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Book> cq = cb.createQuery(Book.class);
            Root<Book> bookRoot = cq.from(Book.class);
            cq.where(cb.equal(bookRoot.get(Book_.author), author));
            bookList = entityManager.createQuery(cq).getResultList();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return bookList;
    }

    public List<Book> getAll() {

        EntityManager entityManager = null;
        List<Book> bookList;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaQuery<Book> cq = cb.createQuery(Book.class);
            Root<Book> book = cq.from(Book.class);
            cq.select(book);
            bookList = entityManager.createQuery(cq).getResultList();
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }

        return bookList;
    }

    public void removeItemBook(int book_id) {
        EntityTransaction transaction = null;
        EntityManager entityManager = null;

        try{
            entityManager = getEntityManagerFactory().createEntityManager();
            Book book = entityManager.find(Book.class, book_id);

            transaction = entityManager.getTransaction();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaUpdate<Book> cq = cb.createCriteriaUpdate(Book.class);
            Root<Book> bookRoot = cq.from(Book.class);
            cq.set(Book_.number_of_instance, book.getNumber_of_instance() - 1).where(cb.equal(bookRoot.get(Book_.id), book_id));

            transaction.begin();
            entityManager.createQuery(cq).executeUpdate();
            transaction.commit();
        } catch (Exception e) {
            e.printStackTrace();
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }

    public void addItemBook(int book_id) {
        EntityTransaction transaction = null;
        EntityManager entityManager = null;

        try {
            entityManager = getEntityManagerFactory().createEntityManager();
            Book book = entityManager.find(Book.class, book_id);

            transaction = entityManager.getTransaction();
            CriteriaBuilder cb = entityManager.getCriteriaBuilder();
            CriteriaUpdate<Book> cq = cb.createCriteriaUpdate(Book.class);
            Root<Book> bookRoot = cq.from(Book.class);
            cq.set(Book_.number_of_instance, book.getNumber_of_instance() + 1).where(cb.equal(bookRoot.get(Book_.id), book_id));

            transaction.begin();
            entityManager.createQuery(cq).executeUpdate();
            transaction.commit();
        } catch (Exception e) {
            e.printStackTrace();
            if (transaction != null && transaction.isActive()) {
                transaction.rollback();
            }
        }finally {
            if (entityManager != null && entityManager.isOpen())
                entityManager.close();
        }
    }
}