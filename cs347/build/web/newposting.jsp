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
        <!--<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.0.0-alpha1/jquery.js"></script>-->
        <title>New Posting - Tutors@JMU</title>
    </head>
    <body>
        <%@include file="header/login_header.jsp" %>
        <div class="jumbotron">
            <div class="container">
                <form class="form-horizontal col-md-offset-1" action="newpost" method="post">
                <div class="form-group">
                    <label for="subject" class="col-sm-2 control-label">Subject:</label>
                    <div class="col-sm-10">
                        <input type="text" class="form-control" id="subject" name="subject" placeholder="Subject" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="comment">Comment:</label>
                    <textarea class="form-control" rows="5" id="comment" name="comment"></textarea>
                </div>
                    <button class="col-md-offset-5 btn btn-info" type="button" onClick="history.go(-1);
                        return true;">Go Back</button>
                   <button type="submit" class="btn btn-success">Submit Post</button>
                </form>
            </div>
        </div>
        <%@include file="footer/footer.jsp" %> 
    </body>
</html>
