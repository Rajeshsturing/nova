'//--------------------------------------------------------------------------
'// NAVO.Cocoon project
'// Copyright NAVO Sp. z o.o. All Rights reserved 2016
'// 
'//--------------------------------------------------------------------------

Imports System.Runtime.InteropServices

Public Class ne_recordset

    Implements IDisposable
    Public Sub New(ByVal oRecordset As Object)
        m_oRecordset = oRecordset
    End Sub
    Public Overloads Sub Dispose() Implements System.IDisposable.Dispose
        Dispose(True)
        GC.SuppressFinalize(Me)
    End Sub
    Private Overloads Sub Dispose(ByVal bDisposing As Boolean)
        If Not m_oRecordset Is Nothing Then
            If bDisposing Then
                'noop
            End If
            Marshal.ReleaseComObject(m_oRecordset)
        End If
        m_oRecordset = Nothing
    End Sub
    Protected Overrides Sub Finalize()
        Dispose(False)
        MyBase.Finalize()
    End Sub
    Public ReadOnly Property EOF() As Boolean
        Get
            Return m_oRecordset.EOF
        End Get
    End Property

    Public Function get_field(ByVal oIndexOrName As Object) As Object
        Return m_oRecordset.Fields.Item(oIndexOrName).Value
    End Function

    Public Function get_field_name(ByVal oIndexOrName As Object) As String
        Return m_oRecordset.Fields.Item(oIndexOrName).Name
    End Function

    Public Function get_field_raw_type(ByVal oIndexOrName As Object) As Integer
        Return m_oRecordset.Fields.Item(oIndexOrName).Type
    End Function

    Public ReadOnly Property field_count As Integer
        Get
            Return m_oRecordset.Fields.Count
        End Get
    End Property
    Public Sub MoveNext()
        m_oRecordset.MoveNext()
    End Sub
    Public Sub MoveTo(iRecordNr As Integer)
        m_oRecordset.Move(iRecordNr, 1)
    End Sub
    Public Iterator Function all() As IEnumerable(Of ne_recordset)
        While Not Me.EOF
            Yield Me
            Me.MoveNext()
        End While
    End Function
    Private m_oRecordset As Object
End Class
