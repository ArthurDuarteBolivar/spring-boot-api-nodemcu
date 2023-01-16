package com.api.nodemcu.controllers;


import com.api.nodemcu.modelo.LoginModelo;
import com.api.nodemcu.repository.LoginRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@CrossOrigin
@RequestMapping("/login")
public class LoginController {

    @Autowired
    private LoginRepository repository;

    @GetMapping("/{name}")
    public List<LoginModelo> list(@PathVariable("name") String name){
        return repository.findByUsuario(name) ;
    }

    @GetMapping
    public List<LoginModelo> listAll(){
        return  repository.findAll();
    }



}
