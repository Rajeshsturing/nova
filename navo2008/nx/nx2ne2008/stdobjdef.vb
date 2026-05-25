Namespace ne2002objdef

    Public Class stdobjdef
        Public Shared Function tablename(ByVal oStdObjDef As Object) As String
            Return oStdObjDef.tablename
        End Function
        Public Shared Function humanname(ByVal oStdObjdef As Object) As String
            Return oStdObjdef.humanname
        End Function
        Public Shared Function getfieldcount(ByVal oStdObjDef As Object) As Int32
            Return oStdObjDef.getfieldcount()
        End Function
        Public Shared Function field(ByVal oStdObjDef As Object, ByVal iIter As Int32) As Object
            Return oStdObjDef.field(iIter)
        End Function
    End Class
End Namespace
