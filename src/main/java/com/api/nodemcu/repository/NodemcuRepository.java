package com.api.nodemcu.repository;

import com.api.nodemcu.model.NodemcuModel;
import jakarta.transaction.Transactional;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Modifying;
import org.springframework.data.jpa.repository.Query;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;
import org.springframework.data.repository.query.Param;

import java.util.List;

//@EnableJpaRepositories
public interface NodemcuRepository extends JpaRepository<NodemcuModel, Integer> {

    List<NodemcuModel> findAll();

    List<NodemcuModel> findByNome(String name);

    <NodemcuMod extends NodemcuModel> NodemcuMod save(NodemcuMod nodemcu);


    @Query(value = "SELECT * FROM thdados WHERE name=:name ORDER BY id DESC LIMIT 1", nativeQuery = true)
    NodemcuModel selectState(@Param("name") String name);
}
