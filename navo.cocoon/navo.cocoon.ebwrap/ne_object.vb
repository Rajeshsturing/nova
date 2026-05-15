'//--------------------------------------------------------------------------
'// NAVO.Cocoon project
'// Copyright NAVO Sp. z o.o. All Rights reserved 2016
'// 
'//--------------------------------------------------------------------------

Imports System.IO
Imports System.Runtime.InteropServices
Imports nxm.system.interop


Public Class ne_object
    Implements IDisposable
    Public Sub New(ByVal oTrans As ne_trans, ByVal oObject As Object)
        m_oTrans = oTrans
        m_oObject = oObject
    End Sub
    Public Overloads Sub Dispose() Implements System.IDisposable.Dispose
        Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub
    Private Overloads Sub Dispose(ByVal bDisposing As Boolean)
        If Not m_oObject Is Nothing Then
            If bDisposing Then
                'noop
            End If
            Marshal.ReleaseComObject(m_oObject)
        End If
        m_oObject = Nothing
    End Sub
    Protected Overrides Sub Finalize()
        Dispose(False)
        MyBase.Finalize()
    End Sub
    Public ReadOnly Property IdObj As Integer
        Get
            Return m_oObject.field(0)
        End Get
    End Property
    Public Function get_field(strFieldName As String) As Object
        Return m_oObject.field(strFieldName)
    End Function
    Public Function get_stream_field(strFieldName As String) As Object
        Dim oFileStream As Object = m_oObject.field(strFieldName)
        If oFileStream Is Nothing Then
            Return Nothing
        Else
            Return New StreamOverIStream(oFileStream)
        End If
    End Function

    Public Function get_ref(strFieldName As String) As ne_object
        Dim value_ = get_field(strFieldName)
        If value_ Is Nothing Then
            Return Nothing
        Else
            Return m_oTrans._wrap_object(value_)
        End If
    End Function

    Public Function get_list(strFieldName As String) As ne_object_list
        Dim value_ = get_field(strFieldName)

        Return m_oTrans._wrap_object_list(m_oObject, strFieldName, value_)
    End Function

    Public Sub set_ref_field(strFieldName As String, value_ As ne_object)
        If value_ Is Nothing Then
            m_oObject.field(strFieldName) = CType(0, Int32)
        Else
            m_oObject.field(strFieldName) = value_._raw_object()
        End If
    End Sub

    Public Sub set_date_field(strFieldName As String, value_ As DateTime)
        m_oObject.field(strFieldName) = value_.Date
    End Sub
    Public Sub set_string_field(strFieldName As String, value_ As String)
        m_oObject.field(strFieldName) = If(value_, "")
    End Sub
    Public Sub set_cy_field(strFieldName As String, value_ As Decimal)
        m_oObject.field(strFieldName) = New CurrencyWrapper(value_)
    End Sub
    Public Sub set_int_field(strFieldName As String, value_ As Integer)
        m_oObject.field(strFieldName) = value_
    End Sub
    Public Sub set_usermodif(value_ As Boolean)
        m_oObject.usermodif(value_)
    End Sub
    Public Function _raw_object() As Object
        Return m_oObject
    End Function

    Protected m_oTrans As ne_trans
    Private m_oObject As Object
End Class
