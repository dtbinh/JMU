<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <!--<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.0.0-alpha1/jquery.js"></script>-->
        <title>Tutors@JMU - Error</title>
    </head>
    <body>
        <jsp:include page="header/header.jsp" />
        <div class="jumbotron">
            <h1 class="text-center">Wow, this is embarrassing.</h1>
            <p class="text-center">We apologize for the inconvenience. Please try again.</p>
            <p class="text-center">If you feel as if there is a problem on our end, do not hesitate to contact us <span><a href="contact">here</a></span>.</p>
            <img src="images/tbservers.png" class="img-responsive" alt="Responsive image" style="max-width: 50%"/>
        </div>
        <jsp:include page="/footer/footer.jsp" />
    </body>
</html>