package org.example;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/tasks")
public class TaskController {
    @Autowired
    private TaskHandler task_handler;

    @GetMapping
    public List<Task> getTasks()
    {
        return task_handler.getTasks();
    }

    @GetMapping("/{id}")
    public Task getTaskById(@PathVariable Integer id)
    {
        return task_handler.getTaskById(id);
    }

    @PostMapping
    @ResponseStatus(HttpStatus.CREATED)
    public Task addTask(@RequestBody Task new_task)
    {
        return task_handler.addTask(new_task);
    }

    @PutMapping("/{id}")
    public Task updateTask(@PathVariable Integer id, @RequestBody Task new_task)
    {
        return task_handler.updateTask(id, new_task);
    }

    @PatchMapping("/{id}")
    public Task updateTaskStatus(@PathVariable Integer id, @RequestBody String new_status)
    {
        return task_handler.updateTaskStatus(id, new_status);
    }

    @DeleteMapping("/{id}")
    @ResponseStatus(HttpStatus.NO_CONTENT)
    public void deleteTask(@PathVariable Integer id)
    {
        task_handler.deleteTask(id);
    }
}
