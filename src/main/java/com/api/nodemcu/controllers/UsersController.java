package com.api.nodemcu.controllers;

import com.api.nodemcu.configs.JwtService;
import com.api.nodemcu.model.PasswordDecode;
import com.api.nodemcu.model.User;
import com.api.nodemcu.repository.UserRepository;
import io.jsonwebtoken.Jwt;
import lombok.RequiredArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.crypto.password.PasswordEncoder;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/api/v1/user")
@RequiredArgsConstructor
public class UsersController {

    @Autowired
    private UserRepository repository;

    private final PasswordEncoder passwordEncoder;
    @Autowired
    private UserRepository userRepository;

    private final JwtService jwtService;


    @GetMapping()
    public List<User> listALl(){
        return repository.findAll();
    }


    @GetMapping("/id")
    public Optional<User> findById(@RequestHeader("Authorization") String authorizationHeader){
        String token = authorizationHeader.replace("Bearer ", "");
        String username = jwtService.extractUsername(token);
        Optional<User> user = userRepository.findByEmail(username);
        return repository.findById(user.get().getId());
    }

    @PostMapping()
    public Boolean FindPassword(@RequestBody PasswordDecode password){
        return passwordEncoder.matches(password.getPassword(), password.getEncodePassword());
    }




}
