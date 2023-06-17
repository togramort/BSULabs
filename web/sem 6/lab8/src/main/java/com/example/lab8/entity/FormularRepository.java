package com.example.lab8.entity;

import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface FormularRepository extends CrudRepository<Formular, Long> {
}
