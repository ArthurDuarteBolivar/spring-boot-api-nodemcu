package com.api.nodemcu.repository;

import com.api.nodemcu.modelo.LoginModelo;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface LoginRepository  extends JpaRepository<LoginModelo, Integer> {

    List<LoginModelo> findById(int id);


}
