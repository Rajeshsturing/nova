Namespace ne2002objdef
    Public Class stdobjdeffield
        Public Shared Function name(ByVal oStdObjdefField As Object) As String
            Return oStdObjdefField.name
        End Function
        Public Shared Function type(ByVal oStdObjdefField As Object) As Int32
            Return oStdObjdefField.type
        End Function
        Public Shared Function sqltype(ByVal oStdObjdefField As Object) As Int32
            Return oStdObjdefField.sqltype
        End Function
        Public Shared Function humanname(ByVal oStdObjdefField As Object) As String
            Return oStdObjdefField.humanname
        End Function
        Public Shared Function reftypeid(ByVal oStdObjdefField As Object) As Int32
            Return oStdObjdefField.reftypeid
        End Function
        Public Shared Function wildreftypeid(ByVal oStdObjdefField As Object, ByVal iInx As Int32) As Int32
            Return oStdObjdefField.wildreftypeid(iInx)
        End Function
        Public Shared Function isrefopt(ByVal oStdObjdefField As Object) As Boolean
            Return oStdObjdefField.isrefopt
        End Function
        Public Shared Function isunique(ByVal oStdObjdefField As Object) As Boolean
            Return oStdObjdefField.isunique
        End Function
        Public Shared Function isnonempty(ByVal oStdObjdefField As Object) As Boolean
            Return oStdObjdefField.isnonempty
        End Function

    End Class
End Namespace
