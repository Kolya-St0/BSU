package org.example;

import com.fasterxml.jackson.databind.ObjectMapper;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.Scanner;

@Component
public class RequestSendler implements CommandLineRunner {

    private final HttpClient client = HttpClient.newHttpClient();
    private final ObjectMapper objectMapper = new ObjectMapper();
    private final Scanner scanner = new Scanner(System.in);
    private final String BASE_URL = "http://localhost:8080/tasks";

    @Override
    public void run(String... args) throws Exception {
        System.out.println("Server: " + BASE_URL);
        System.out.println("Database: http://localhost:8080/h2-console");
        while (true) {
            printMenu();
            String choice = scanner.nextLine().trim();
            try {
                switch (choice) {
                    case "1" -> getAllTasks();
                    case "2" -> getTaskById();
                    case "3" -> createTask();
                    case "4" -> updateTask();
                    case "5" -> updateTaskStatus();
                    case "6" -> deleteTask();
                    case "0" -> {
                        System.out.println("Exit");
                        return;
                    }
                    default -> System.out.println("Invalid input");
                }
            }
            catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
            }
        }
    }

    private void printMenu() {
        System.out.println("════════════════ MENU ════════════════");
        System.out.println("1. GET/tasks");
        System.out.println("2. GET/tasks/{id}");
        System.out.println("3. POST/tasks");
        System.out.println("4. PUT/tasks/{id}");
        System.out.println("5. PATCH/tasks/{id}");
        System.out.println("6. DELETE/tasks/{id}");
        System.out.println("0. Exit");
        System.out.println("═══════════════════════════════════════");
    }

    private void getAllTasks() {
        System.out.println("GET/tasks");
        try {
            HttpRequest request = HttpRequest.newBuilder().uri(URI.create(BASE_URL)).header("Content-Type", "application/json").GET().build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println("Status: " + response.statusCode());
            System.out.println("Response:");
            System.out.println(formatJson(response.body()));
        }
        catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private void getTaskById() {
        System.out.print("GET/tasks/{id}\nEnter task ID: ");
        String id = scanner.nextLine().trim();
        try {
            HttpRequest request = HttpRequest.newBuilder().uri(URI.create(BASE_URL + "/" + id)).header("Content-Type", "application/json")
                    .GET().build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println("Status: " + response.statusCode());
            System.out.println("Response:");
            System.out.println(formatJson(response.body()));
        }
        catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private void createTask() {
        System.out.println("POST/tasks");
        try {
            System.out.print("Enter title: ");
            String title = scanner.nextLine().trim();

            System.out.print("Enter description: ");
            String description = scanner.nextLine().trim();

            System.out.println("Enter status (todo, in_progress, done):  ");
            String status = scanner.nextLine().trim();
            if(!status.equals("todo") && !status.equals("in_progress") && !status.equals("done")){
                status = "todo";
            }
            String jsonBody = String.format("{\"title\":\"%s\",\"description\":\"%s\",\"status\":\"%s\"}", title, description, status);

            HttpRequest request = HttpRequest.newBuilder().uri(URI.create(BASE_URL)).header("Content-Type", "application/json")
                    .POST(HttpRequest.BodyPublishers.ofString(jsonBody)).build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println("Status: " + response.statusCode());
            System.out.println("Response:");
            System.out.println(formatJson(response.body()));
        }
        catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private void updateTask() {
        System.out.print("PUT/tasks/{id}\nEnter ID: ");
        String id = scanner.nextLine().trim();
        try {
            System.out.print("Enter new title: ");
            String title = scanner.nextLine().trim();

            System.out.print("Enter new description: ");
            String description = scanner.nextLine().trim();

            System.out.println("Enter new status (todo, in_progress, done): ");
            String status = scanner.nextLine().trim();
            if(!status.equals("todo") && !status.equals("in_progress") && !status.equals("done")){
                status = "todo";
            }
            String jsonBody = String.format("{\"title\":\"%s\",\"description\":\"%s\",\"status\":\"%s\"}", title, description, status);

            HttpRequest request = HttpRequest.newBuilder().uri(URI.create(BASE_URL + "/" + id)).header("Content-Type", "application/json")
                    .PUT(HttpRequest.BodyPublishers.ofString(jsonBody)).build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println("Status: " + response.statusCode());
            System.out.println("Response:");
            System.out.println(formatJson(response.body()));
        }
        catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private void updateTaskStatus() {
        System.out.print("PATCH/tasks/{id}\nEnter ID: ");
        String id = scanner.nextLine().trim();
        try {
            System.out.println("Enter new status (todo, in_progress, done):");
            String new_status = scanner.nextLine().trim();
            if(!new_status.equals("todo") && !new_status.equals("in_progress") && !new_status.equals("done")){
                new_status = "todo";
            }

            HttpRequest request = HttpRequest.newBuilder().uri(URI.create(BASE_URL + "/" + id)).header("Content-Type", "application/json")
                    .method("PATCH", HttpRequest.BodyPublishers.ofString(new_status)).build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println("Status: " + response.statusCode());
            System.out.println("Response:");
            System.out.println(formatJson(response.body()));
        }
        catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private void deleteTask() {
        System.out.print("DELETE/tasks/{id}\nEnter ID: ");
        String id = scanner.nextLine().trim();
        try {
            HttpRequest request = HttpRequest.newBuilder().uri(URI.create(BASE_URL + "/" + id)).header("Content-Type", "application/json")
                    .DELETE().build();
            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());

            System.out.println("Status: " + response.statusCode());
            System.out.println("Response: " + response.body());
        }
        catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    private String formatJson(String json) {
        try {
            Object jsonObject = objectMapper.readValue(json, Object.class);
            return objectMapper.writerWithDefaultPrettyPrinter().writeValueAsString(jsonObject);
        }
        catch (Exception e) {
            return json;
        }
    }
}