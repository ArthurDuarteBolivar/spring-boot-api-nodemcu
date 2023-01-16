package com.api.nodemcu.modelo;


import javax.persistence.*;
import java.util.Date;

@Entity
@Table(name="login")
public class LoginModelo {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(name = "ID")
    private int id;

    @Column(name = "usuario", unique = true)
    private String usuario;

    @Column(name = "senha")
    private int senha;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getUsuario() {
        return usuario;
    }

    public void setUsuario(String usuario) {
        this.usuario = usuario;
    }

    public int getSenha() {
        return senha;
    }

    public void setSenha(int senha) {
        this.senha = senha;
    }
}
