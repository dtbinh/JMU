<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.0.0-alpha1/jquery.js"></script>
<!--        <script type="text/javascript">
            window.setTimeout(function () {
                $("#alert_message").fadeTo(500, 0).slideUp(500, function () {
                    $(this).remove();
                });
            }, 3000);
        </script>-->
        <title>Tutors@JMU - Reset Fail</title>
    </head>
    <body>
        <jsp:include page="header/header.jsp" />
        <s:if test="hasActionErrors()">
            <div class="alert alert-danger" id="alert_message">
                <s:actionerror/>
            </div>
        </s:if>
        <div class="jumbotron">
            <h1 class="text-center">The Password Reset Has Failed</h1>
            <p class="text-center">Please submit another request<span><a href="pass_reset">  Here</a></span></p>
        </div>
        <jsp:include page="/footer/footer.jsp" />
    </body>
</html>
