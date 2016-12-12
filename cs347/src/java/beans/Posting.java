/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package beans;

/**
 *
 * @author winterpa
 */
public class Posting 
{
    public String postID;
    public String name;

    public String getPostID() {
        return postID;
    }

    public void setPostID(String postID) {
        this.postID = postID;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public String getTimeCreated() {
        return timeCreated;
    }

    public void setTimeCreated(String timeCreated) {
        this.timeCreated = timeCreated;
    }

    public String getTimeRequested() {
        return timeRequested;
    }

    public void setTimeRequested(String timeRequested) {
        this.timeRequested = timeRequested;
    }

    public String getSubjects() {
        return subjects;
    }

    public void setSubjects(String subjects) {
        this.subjects = subjects;
    }

    public String getMsg() {
        return msg;
    }

    public void setMsg(String msg) {
        this.msg = msg;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
    public String type;
    public String timeCreated;
    public String timeRequested;
    public String subjects;
    public String msg;
    public String status;
    
    public Posting()
    {
        postID = "";
        name = "";
        type = "";
        timeCreated = "";
        timeRequested = "";
        subjects = "";
        msg = "";
        status = "";
    }
    
    public String toString()
    {
        return "Posting: " + postID + " " + name + " " + type + " " +
            timeCreated + " " + timeRequested + " " + subjects +
                    " " + msg + " " + status;
    }
}
