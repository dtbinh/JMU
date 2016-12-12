<%-- 
    Document   : email_success
    Created on : Nov 21, 2015, 4:20:20 AM
    Author     : jhd29_000
--%>

<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <title>Tutors@JMU - Email Success</title>
    </head>
    <body>
        <%@include file="header/header.jsp" %> 
        <div class="jumbotron">
            <h1 class="text-center">An email has been sent to you.</h1>
            <p class="text-center">Please check your email for instructions on how to reset your password.</p>
            <p class="text-center">You can now close this window.</p>
        </div>
        <jsp:include page="/footer/footer.jsp" />
    </body>
</html>
