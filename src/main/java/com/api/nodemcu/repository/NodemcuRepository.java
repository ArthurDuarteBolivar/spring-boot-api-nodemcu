package com.api.nodemcu.repository;

import com.api.nodemcu.modelo.NodemcuModelo;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface NodemcuRepository extends JpaRepository<NodemcuModelo, Integer> {

    List<NodemcuModelo> findAll();

    <NodemcuMod extends NodemcuModelo> NodemcuMod save(NodemcuMod nodemcu);

}
