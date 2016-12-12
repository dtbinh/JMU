<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>

    <%
        String token = request.getParameter("token");
        System.out.println("The token is: " + token);
        session.setAttribute("token", token);
        session.setAttribute("activation-time", System.currentTimeMillis());
        System.out.println("Sending the token to servlet...");
    %>

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
        <title>Change Password</title>
    </head>
    <body>
<!--    <s:if test="hasActionErrors()">
        <div class="alert alert-danger" id="alert_message">
            <s:actionerror/>
        </div>
    </s:if>-->
    <jsp:include page="header/header.jsp" />
    <div class="jumbotron">
        <div class="col-md-offset-3">
            <h1 class="col-md-offset-2">Change Password</h1>
            <hr>
            <p class="col-md-offset-1">Please make sure that the new typed password matches the confirmation.</p>
            <p class="col-md-offset-3">This is a one time submission.</p>
            <hr>
            <form class="form-horizontal col-md-offset-2" action="change" method="post">  
                <div class="form-group ">
                    <label for="password" class="col-sm-2 control-label">Password:</label>
                    <div class="col-sm-10">
                        <input type="password" class="form-control" id="password" name="password" placeholder="New Password" >
                    </div>
                </div>
                <div class="form-group">
                    <label for="passwordConf" class="col-sm-2 control-label">Confirm:</label>
                    <div class="col-sm-10">
                        <input type="password" class="form-control" id="passwordConf" name="passwordConf" placeholder="Confirm Password">
                    </div>
                </div>
                <div class="form-group">
                    <div class="col-sm-offset-2 col-sm-10">
                        <button type="button" class="btn btn-default" onClick="history.go(-1);
                                return true;">Go Back</button>
                        <button type="submit" class="btn btn-default">Sign in</button>
                    </div>
                </div>
            </form>        
        </div>
    </div>
  <jsp:include page="/footer/footer.jsp" />
</body>
</html>
