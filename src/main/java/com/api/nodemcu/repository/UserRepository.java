package com.api.nodemcu.repository;

import java.util.List;
import java.util.Optional;

import com.api.nodemcu.model.User;
import org.springframework.data.jpa.repository.JpaRepository;

public interface UserRepository extends JpaRepository<User, Integer> {

    Optional<User> findByEmail(String email);

    Optional<User> findById(Integer id);

    List<User> findAll();

    <UsersMod extends User> UsersMod save(UsersMod entity);

}
