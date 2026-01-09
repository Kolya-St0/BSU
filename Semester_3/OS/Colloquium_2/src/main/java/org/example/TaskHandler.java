package org.example;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.cache.annotation.CacheEvict;
import org.springframework.cache.annotation.CachePut;
import org.springframework.cache.annotation.Cacheable;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class TaskHandler {
    private static final Logger log = LoggerFactory.getLogger(TaskHandler.class);
    @Autowired
    private TaskRepository task_repository;

    //GET/tasks
    @Cacheable("tasksList")
    public List<Task> getTasks() {
        return task_repository.findAll();
    }

    //GET/tasks/{id}
    @Cacheable(value = "taskSingle", key = "#id")
    public Task getTaskById(Integer id) {
        return task_repository.findById(id).orElseThrow(() -> {
            log.error("Task with ID {} not found", id);
            throw new RuntimeException("Task not found");
        });
    }

    //POST/tasks
    @CacheEvict(value = "tasksList", allEntries = true)
    public Task addTask(Task task) {
        return task_repository.save(task);
    }

    //PUT/tasks/{id}
    @CacheEvict(value = "tasksList", allEntries = true)
    @CachePut(value = "taskSingle", key = "#id")
    public Task updateTask(Integer id, Task newTask) {
        Task existingTask = getTaskById(id);

        existingTask.setTitle(newTask.getTitle());
        existingTask.setDescription(newTask.getDescription());
        existingTask.setStatus(newTask.getStatus());

        return task_repository.save(existingTask);
    }

    //PATCH/tasks/{id}
    @CacheEvict(value = "tasksList", allEntries = true)
    @CachePut(value = "taskSingle", key = "#id")
    public Task updateTaskStatus(Integer id, String newStatus) {
        Task task = getTaskById(id);
        task.setStatus(newStatus);
        return task_repository.save(task);
    }

    //DELETE/tasks/{id}
    @CacheEvict(value = {"tasksList", "taskSingle"}, allEntries = true)
    public void deleteTask(Integer id) {
        if (!task_repository.existsById(id)) {
            log.warn("Task with this ID don't exist: {}", id);
            return;
        }
        task_repository.deleteById(id);
    }
}
