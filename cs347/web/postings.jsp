<%@page import="beans.Posting"%>
<%@page import="java.util.ArrayList"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<%
    System.out.println("Outside postings.jsp... value of inputUser:  " + request.getParameter("inputUser"));
    System.out.println("Printing username session attribute from postings: " + session.getAttribute("username"));
    try {
        Boolean isLoggedInNow
                = ((Boolean) (session.getAttribute("loggedIn")));
        if (!isLoggedInNow.booleanValue() || isLoggedInNow == null) {
            String url = "http://" + request.getServerName() + ":8080" + request.getContextPath() + "/login.jsp";
            response.sendRedirect(response.encodeRedirectURL(url));
        } else {
            System.out.println("Inside postings.jsp else statement. The user is logged in!");
        }
    } catch (NullPointerException e) {
        String url = "http://" + request.getServerName() + ":8080" + request.getContextPath() + "/login.jsp";
        response.sendRedirect(response.encodeRedirectURL(url));
    }
%>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.0.0-alpha1/jquery.js"></script>
        <script type="text/javascript">        
        window.setTimeout(function() {
            $("#alert_message_success").fadeTo(500, 0).slideUp(500, function(){
                $(this).remove(); 
            });
        }, 3000);
        </script>
        <title>Tutors@JMU - Postings</title>
    </head>
    <body>
        <%@include file="header/login_header.jsp" %>
        <jsp:useBean id="postDao" class="beans.PostingDao"/>
        <s:if test="hasActionMessages()">
            <div class="alert alert-success message" id="alert_message_success">
                 <s:actionmessage/>
            </div>
                </s:if>
        <button type="button" class="btn btn-success col-md-offset-11" name="newposting" onclick="window.location.href='newposting.jsp'">Create Post</button>
        <h1 class="text-center">Welcome Back, 
            <span id="welcome" style="text-transform: capitalize !important;">
                <%= session.getAttribute("username") %>!</span></h1> 
                <br>
                <p class="text-center">Below will contain all of the posts available. The user should be able to only edit/delete their own posts, and be able to click on a persons post.</p>
                <table class="table table-hover">
                    <thead>
                        <tr>
                          <th>Post ID</th>
                          <th>Name</th>
                          <th>Type</th>
                          <th>Date of Post</th>
                          <th>Meeting Time</th>
                          <th>Subjects</th>
                          <th>Message</th>
                          <th>Status</th>
                        </tr>
                    </thead>
                    <tbody>
                <%
                    ArrayList<Posting> postings = postDao.getPostings(); 
                    
                    for (Posting p : postings)
                    { %>       
                        <tr>
                          <td><%= p.postID%></td>
                          <td><%= p.name%></td>
                          <td><%= p.type%></td>
                          <td><%= p.timeCreated%></td>
                          <td><%= p.timeRequested%></td>
                          <td><%= p.subjects%></td>
                          <td><%= p.msg%></td>
                          <td><%= p.status%></td>
                        </tr>
                    <% } %>
                    </tbody>
                </table>
                <%@include file="footer/footer.jsp" %> 
    </body>
</html>
