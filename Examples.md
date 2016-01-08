
format:
```
{
    "type": "ROS msg data type",
    "topic": "rostopic to publish too",
    "iter": "how many times should it be published",
    "data": {
        "field type": "value"
        .
        .
        .
    }
}
```


```json
{
    "type": "geometry_msgs::Twist",     
    "topic": "/chatter",
    "iter": "40",
    "data": {
        "linear.x": "30",
        "linear.y": "30",
        "linear.z": "45",
        "angular.x": "0",
        "angular.y": "0",
        "angular.z": "0"
    } 
}
```


```
{
    "data": "std_msgs::String",
    "topic": "/chatter"
    "itter": "1",
    "set": {
        "data": "hello world"
    }
}
```
