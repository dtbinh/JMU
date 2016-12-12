<%@page import="java.util.ArrayList"%>
<%@page import="beans.UserDao"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<%
    System.out.println("Printing username session attribute from profile " + session.getAttribute("username"));
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
        <title>Tutors@JMU - Profile</title>
    </head>
    <body>
        <%@include file="header/login_header.jsp" %> 
        
        <h1 class="text-center" id="welcome" style="text-transform: capitalize !important;"><%= session.getAttribute("username") %>'s Profile</h1>
        <br>
        <p class="text-center"><span>Would you like to change your password? Please click the link to <a href="pass_reset"> Reset Now.</a></span></p>
        <br>
        
        <form class="form-horizontal col-md-offset-3" action="update_profile" method="post" autocomplete="on">
                <div class="form-group">
                    <label for="inputUserReg" class="col-sm-2 control-label">Username:</label>
                    <div class="col-sm-10">
                        <input type="text" class="form-control" id="inputUserReg" name="inputUserReg"  >
                    </div>
                </div>
                <div class="form-group">
                    <label for="inputEmail" class="col-sm-2 control-label">Email:</label>
                    <div class="col-sm-10">
                        <input type="email" class="form-control" id="inputEmail" name="inputEmail">
                    </div>
                </div>
                <div class="form-group">
                    <label for="inputFirstName" class="col-sm-2 control-label">First Name:</label>
                    <div class="col-sm-10">
                        <input type="text" class="form-control" id="inputFirstName" name="inputFirstName" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="inputLastName" class="col-sm-2 control-label">Last Name:</label>
                    <div class="col-sm-10">
                        <input type="text" class="form-control" id="inputLastName" name="inputLastName" >
                    </div>
                </div>
                <div class="form-group">
                    <p class="tutoring_classes_heading">Please select classes for tutoring. (This is Optional.)</p>
                    <input type="checkbox" name="classes" value="Business">Business
                    <input type="checkbox" name="classes" value="Chemistry">Chemistry
                    <input type="checkbox" name="classes" value="Computer Science">Computer Science
                    <input type="checkbox" name="classes" value="English">English
                    <input type="checkbox" name="classes" value="Health Science">Health Science<br>
                    <input type="checkbox" name="classes" value="Math">Math
                    <input type="checkbox" name="classes" value="Nursing">Nursing
                    <input type="checkbox" name="classes" value="Philosophy">Philosophy
                    <input type="checkbox" name="classes" value="Psychology">Psychology
                    <input type="checkbox" name="classes" value="Science">Science
                </div>
                <br>
                <div class="col-md-offset-1">
                    <fieldset>
                        <legend>Account Type</legend>
                        <label for="student">
                            <input type="radio"
                                   name="radio"
                                   id="student" value="Student" checked="checked" />Student</label>
                        <label for="tutor">
                            <input type="radio"
                                   name="radio"
                                   id="tutor" value="Tutor" />Tutor</label>
                    </fieldset>
                </div>
                <br>
                <div class="form-group">
                    <div class="col-sm-offset-2 col-sm-10">
                        <button type="button" class="btn btn-default" onClick="history.go(-1);
                                return true;">Go Back</button>
                        <button type="submit" class="btn btn-default">Update</button>
                    </div>
                </div>
            </form>
                <%@include file="footer/footer.jsp" %> 
    </body>
</html>
