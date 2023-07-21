package com.api.nodemcu.auth;


import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

import lombok.RequiredArgsConstructor;

@RestController
@RequestMapping("/api/v1/auth")
@RequiredArgsConstructor
public class AuthenticationController {

    private final AuthenticationService authenticationService;

    @PostMapping("/register")
    public ResponseEntity<AuthenticationResponse> register(@RequestBody RegisterRequest request) {
        return ResponseEntity.ok(authenticationService.register(request));
    }

    @PostMapping("/authenticate")
    public ResponseEntity<?> register(@RequestBody AuthenticationRequest request) {
        AuthenticationResponse token = authenticationService.authenticate(request);
        if (token.getToken() != null){
            return ResponseEntity.ok(authenticationService.authenticate(request));
        }
        throw new IllegalArgumentException("Email ou senha não coencidem");
    }


}
