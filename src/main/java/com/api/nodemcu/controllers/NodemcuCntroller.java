package com.api.nodemcu.controllers;

import com.api.nodemcu.model.NodemcuModel;
import com.api.nodemcu.model.User;
import com.api.nodemcu.repository.NodemcuRepository;
import com.api.nodemcu.repository.UserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/api/v1/nodemcu")
public class NodemcuCntroller {

    @Autowired
    private NodemcuRepository repository;

    @Autowired
    private UserRepository userRepository;

    @GetMapping()
    public List<NodemcuModel> list(){
        return repository.findAll();
    }


    @GetMapping("/{name}")
    public List<NodemcuModel> listNome(@PathVariable("name") String name){
        return repository.findByNome(name);
    }



    @PostMapping()
    public NodemcuModel post(@RequestBody NodemcuModel device, @RequestParam("email") String userEmail) {
        Optional<User> user = userRepository.findByEmail(userEmail);
        if (user.isPresent()) {
            if(device.getNome().isEmpty()){
                throw new RuntimeException("Nome invalido");
            }else{
                device.setId_user(user.get());
                repository.save(device);
                return device;
            }
        } else {
            throw new IllegalArgumentException("Usuário não encontrado");
        }
    }


    @GetMapping("/desc/{name}")
    public NodemcuModel listNomeOne(@PathVariable("name") String name){
        return repository.selectState(name);
    }


}