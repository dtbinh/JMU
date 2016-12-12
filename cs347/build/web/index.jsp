<%@page import="org.apache.struts2.ServletActionContext"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>

<!DOCTYPE html>
<%
    System.out.println("Outside of index.jsp... value of inputUser: " + request.getParameter("inputUser"));
    if (session.getAttribute("loggedIn") != null && session.getAttribute("loggedIn").equals("true"))
    {
        System.out.print("Inside index.jsp... value of inputUser: " + request.getParameter("inputUser"));
        response.sendRedirect("postings.jsp");
    } else {
        System.out.println("First Time in index.jsp");
    }
%> 
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <title>Tutors@JMU - Home</title>
    </head>
    <body>
        <%@include file="header/header.jsp" %> 
        <div class="container text-center" id="home-container">
            <h1 class="welcome-heading">Welcome To Tutors@JMU!</h1>
            <hr>
            <div class="container-fluid" id="img-overlay">
                <div class="row">
                    <img src="images/homeimage.jpg" class="img-responsive">
                </div>
            </div>
        </div>
        <%@include file="footer/footer.jsp" %> 
    </body>
</html>
