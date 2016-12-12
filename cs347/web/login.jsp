<%@page contentType="text/html" pageEncoding="UTF-8"%>
<%@ taglib prefix="s" uri="/struts-tags" %>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="stylesheet" type="text/css" href="stylesheets/tutorstyle.css">
        <link rel="stylesheet" type="text/css" href="stylesheets/bootstrap.css">
        <script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.0.0-alpha1/jquery.js"></script>
        <title>Tutors@JMU - Login</title>
        <script type="text/javascript">
            window.setTimeout(function () {
                $("#alert_message").fadeTo(500, 0).slideUp(500, function () {
                    $(this).remove();
                });
            }, 3000);

            window.setTimeout(function () {
                $("#alert_message_success").fadeTo(500, 0).slideUp(500, function () {
                    $(this).remove();
                });
            }, 7000);
        </script>
    </head>
    <body>
        <jsp:include page="header/header.jsp" />
        <s:if test="hasActionErrors()">
            <div class="alert alert-danger" id="alert_message">
                <s:actionerror/>
            </div>
        </s:if>
        <s:if test="hasActionMessages()">
            <br><br>
            <div class="alert alert-success message" id="alert_message_success">
                <s:actionmessage/>
            </div>
        </s:if>
        <div class="jumbotron">
            <div class="col-md-offset-3">
                <h1 class="col-md-offset-3">Login</h1>
                <hr>
                <form class="form-horizontal col-md-offset-1" action="login" method="post">

                    <div class="form-group">
                        <label for="inputUser" class="col-sm-2 control-label">Username:</label>
                        <div class="col-sm-10">
                            <input type="text" class="form-control" id="inputUser" name="inputUser" placeholder="User" >
                            <%--<s:property value="fieldErrors['user']"></s:property>--%>
                        </div>
                    </div>
                    <div class="form-group">
                        <label for="inputPassword" class="col-sm-2 control-label">Password:</label>
                        <div class="col-sm-10">
                            <input type="password" class="form-control" id="inputPassword" name="inputPassword" placeholder="Password">
                            <%--<s:property value="fieldErrors.get('password')"></s:property>--%>
                        </div>
                    </div>
                    <div class="form-group">
                        <div class="col-sm-offset-2 col-sm-10">
                            <div class="checkbox">
                                <label>
                                    <input type="checkbox"> Remember me
                                </label>                    
                                <span class="col-sm-offset-1"><a href="pass_reset">Forgotten Password?</a></span>
                            </div>
                        </div>
                    </div>
                    <div class="form-group">
                        <div class="col-sm-offset-2 col-sm-10">
                            <button type="button" class="btn btn-default" onClick="history.go(-1);
                                    return true;">Go Back</button>
                            <button type="submit" class="btn btn-default">Sign in</button>
                        </div>
                    </div>
            </div>
        </form>        
    </div>
    <jsp:include page="/footer/footer.jsp" />
</body>
</html>
