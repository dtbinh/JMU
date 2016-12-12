<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.0.0-alpha1/jquery.js"></script>
        <script type="text/javascript">
            window.setTimeout(function () {
                $("#alert_message").fadeTo(500, 0).slideUp(500, function () {
                    $(this).remove();
                });
            }, 3000);
        </script>
        <title>Password Reset</title>
        <script>
            function goBack() {
                window.location.replace("profile.jsp");
            }
        </script>
    </head>
    <body>
        <%
            try {
                Boolean isLoggedInNow
                        = ((Boolean) (session.getAttribute("loggedIn")));
                if (!isLoggedInNow.booleanValue() || isLoggedInNow == null) {
        %>    
        <jsp:include page='<%="header/header.jsp"%>'/>
        <%
        } else {
        %>    
        <jsp:include page='<%="header/login_header.jsp"%>'/>
        <%
            }
        } catch (NullPointerException e) {
        %>
        <jsp:include page='<%="header/header.jsp"%>'/>
        <%
            }
        %>
        <s:if test="hasActionErrors()">
            <div class="alert alert-danger" id="alert_message">
                <s:actionerror/>
            </div>
        </s:if>

        <div class="jumbotron">
            <h1 class="text-center">Password Reset</h1>
            <hr>
            <p class="text-center">Please type in your email. You will be sent a one time link to reset your password.</p>
            <br>
            <form class="form-horizontal col-md-offset-3" action="password" method="post">
                <div class="form-group">
                    <label for="inputEmail" class="col-sm-2 control-label">Email: </label>
                    <div class="col-sm-10">
                        <input type="email" class="form-control" id="inputEmail" name="inputEmail" >
                    </div>
                </div>
                <div class="form-group">
                    <div class="col-sm-offset-2 col-sm-10">
                        <button type="button" class="btn btn-default" onClick="goBack()">Go Back</button>
                        <button type="submit" class="btn btn-default">Send Email</button>
                    </div>
                </div>
            </form>
        </div>
        <jsp:include page="/footer/footer.jsp" />
    </body>
</html>
