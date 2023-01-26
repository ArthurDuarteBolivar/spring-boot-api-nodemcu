package com.api.nodemcu.repository;

import com.api.nodemcu.modelo.LoginModelo;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.Query;

import java.util.List;

public interface LoginRepository  extends JpaRepository<LoginModelo, Integer> {


    List<LoginModelo> findAll();

    List<LoginModelo> findByUsuario(String name);


}
