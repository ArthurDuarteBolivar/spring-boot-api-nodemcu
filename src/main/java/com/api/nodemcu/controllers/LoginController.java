package com.api.nodemcu.controllers;


import com.api.nodemcu.modelo.LoginModelo;
import com.api.nodemcu.repository.LoginRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/logins")
public class LoginController {

    @Autowired
    private LoginRepository repository;

    @GetMapping("/{name}")
    @PreAuthorize("hasRole('MANAGERS')")
    public List<LoginModelo> list(@PathVariable("name") String name){
        return repository.findByUsuario(name) ;
    }

    @GetMapping
    @PreAuthorize("hasRole('MANAGERS')")
    public List<LoginModelo> listAll(){
        return  repository.findAll();
    }



}
