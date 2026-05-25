Imports ADODB
Imports System.Runtime.InteropServices
Imports nxappcore

'-----------------------------------------------
' browse data adapter dla Browsehelpera
'
'-----------------------------------------------
Namespace BDA

    Public Interface IBrowseDataAdapter_
        ReadOnly Property EOF() As Boolean
        ReadOnly Property BOF() As Boolean
        ReadOnly Property record_number() As Integer
        Sub MoveNext()
        Sub MovePrev()
        Sub MoveBy(ByVal iRecordsToSkip As Integer)
        Sub MoveTo(ByVal iRecordNumber As Integer)
        Function field(ByVal iIndex As Integer) As Object
        Function field_count() As Integer

        Function record_id() As Integer
        Function record_type() As Integer
        Function record_string() As String
    End Interface

    '-----------------------------------------------
    ' BDA na Recordset ADO
    '-----------------------------------------------

    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_adorecordsetbda)> _
    Public Class ADORecordsetBDA
        Implements IBrowseDataAdapter_

        Public Sub New(ByVal oRecordSet As Recordset)
            m_oRecordSet = oRecordSet
            m_iRecordNumber = 0
        End Sub
        Public ReadOnly Property EOF() As Boolean Implements IBrowseDataAdapter_.EOF
            Get
                Return m_oRecordSet.EOF
            End Get
        End Property
        Public ReadOnly Property BOF() As Boolean Implements IBrowseDataAdapter_.BOF
            Get
                Return m_oRecordSet.BOF
            End Get
        End Property

        Public Function record_id() As Integer Implements IBrowseDataAdapter_.record_id
            Return CInt(field(0))
        End Function
        Public Function record_type() As Integer Implements IBrowseDataAdapter_.record_type
            Return CInt(field(2))
        End Function
        Public Function record_string() As String Implements IBrowseDataAdapter_.record_string
            Return CStr(field(1))
        End Function

        Public Function field(ByVal iIndex As Integer) As Object Implements IBrowseDataAdapter_.field
            Return m_oRecordSet.Fields.Item(iIndex).Value
        End Function

        Public Function field_count() As Integer Implements IBrowseDataAdapter_.field_count
            Return m_oRecordSet.Fields.Count
        End Function
        ReadOnly Property record_number() As Integer Implements IBrowseDataAdapter_.record_number
            Get
                Return m_iRecordNumber
            End Get
        End Property
        Public Sub MoveNext() Implements IBrowseDataAdapter_.MoveNext
            m_oRecordSet.MoveNext()
            m_iRecordNumber += 1
        End Sub
        Public Sub MovePrev() Implements IBrowseDataAdapter_.MovePrev
            m_oRecordSet.MovePrevious()
            m_iRecordNumber -= 1
        End Sub
        Public Sub MoveBy(ByVal iRecordsToSkip As Integer) Implements IBrowseDataAdapter_.MoveBy
            If iRecordsToSkip <> 0 Then
                m_oRecordSet.Move(iRecordsToSkip)
                m_iRecordNumber += iRecordsToSkip
            End If
        End Sub

        Sub MoveTo(ByVal iRecordNumber As Integer) Implements IBrowseDataAdapter_.MoveTo
            MoveBy(iRecordNumber - m_iRecordNumber)
        End Sub

        Private m_oRecordSet As Recordset
        Private m_iRecordNumber As Integer
    End Class

    '-----------------------------------------------
    ' BDA na obiekcie (VBScript)
    ' CustomBDA jest tylko czystym forwarderem do prawdziwego obiektu
    '-----------------------------------------------
    Public Class CustomBDA
        Implements IBrowseDataAdapter_
        Public Sub New(ByVal oCustomData As Object)
            m_oCustomData = oCustomData
        End Sub
        Public ReadOnly Property EOF() As Boolean Implements IBrowseDataAdapter_.EOF
            Get
                Return m_oCustomData.EOF
            End Get
        End Property
        Public ReadOnly Property BOF() As Boolean Implements IBrowseDataAdapter_.BOF
            Get
                Return m_oCustomData.BOF
            End Get
        End Property
        Public Function record_id() As Integer Implements IBrowseDataAdapter_.record_id
            Return m_oCustomData.field(0)
        End Function
        Public Function record_type() As Integer Implements IBrowseDataAdapter_.record_type
            Return m_oCustomData.field(2)
        End Function
        Public Function record_string() As String Implements IBrowseDataAdapter_.record_string
            Return m_oCustomData.field(1)
        End Function

        Public Function field(ByVal iIndex As Integer) As Object Implements IBrowseDataAdapter_.field
            Return m_oCustomData.field(iIndex)
        End Function

        Public Function field_count() As Integer Implements IBrowseDataAdapter_.field_count
            Return m_oCustomData.field_count()
        End Function
        ReadOnly Property record_number() As Integer Implements IBrowseDataAdapter_.record_number
            Get
                Return m_oCustomData.record_number
            End Get
        End Property

        Public Sub MoveNext() Implements IBrowseDataAdapter_.MoveNext
            m_oCustomData.MoveNext()
        End Sub
        Public Sub MovePrev() Implements IBrowseDataAdapter_.MovePrev
            m_oCustomData.MovePrev()
        End Sub
        Public Sub MoveBy(ByVal iRecordsToSkip As Integer) Implements IBrowseDataAdapter_.MoveBy
            m_oCustomData.MoveBy(iRecordsToSkip)
        End Sub
        Sub MoveTo(ByVal iRecordNumber As Integer) Implements IBrowseDataAdapter_.MoveTo
            m_oCustomData.MoveTo(iRecordNumber)
        End Sub

        Private m_oCustomData As Object
    End Class

    '-----------------------------------------------
    ' BDA na tablicy - wyswietlana jest zwartosc tablicy
    ' zwracany indeks w tablicy
    '-----------------------------------------------

    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_nxarraybda)> _
    Public Class NXArrayBDA
        Implements IBrowseDataAdapter_

        Public Sub New(ByVal oNXArray As nxarray)
            m_oNXArray = oNXArray
            m_oFilterArray = New nxarray
            For iter As Integer = 0 To m_oNXArray.count - 1
                m_oFilterArray.add(False)
            Next
            Reset()
        End Sub
        Public ReadOnly Property EOF() As Boolean Implements IBrowseDataAdapter_.EOF
            Get
                Return (m_iPosition >= m_oNXArray.count)
            End Get
        End Property
        Public ReadOnly Property BOF() As Boolean Implements IBrowseDataAdapter_.BOF
            Get
                Return (m_iPosition <= 0)
            End Get
        End Property
        ReadOnly Property record_number() As Integer Implements IBrowseDataAdapter_.record_number
            Get
                Return m_iRecordNumber
            End Get
        End Property
        Public Overridable Function record_id() As Integer Implements IBrowseDataAdapter_.record_id
            Return m_iPosition  'works as 'idobj'
        End Function
        Public Overridable Function record_type() As Integer Implements IBrowseDataAdapter_.record_type
            Return 1    'works as typeid
        End Function
        Public Overridable Function record_string() As String Implements IBrowseDataAdapter_.record_string
            Return m_oNXArray(m_iPosition) 'works as 'value
        End Function

        Public Overridable Function field(ByVal iIndex As Integer) As Object Implements IBrowseDataAdapter_.field
            Select Case iIndex
                Case 0
                    Return m_iPosition  'works as 'idobj'
                Case 1
                    Return m_oNXArray(m_iPosition) 'works as 'value
                Case 2
                    Return 1    'works as typeid
                Case Else
                    Throw New nxexception("NXArrayBDA:field: invalid iIndex=" + iIndex.ToString())
            End Select
        End Function

        Public Overridable Function should_be_filtered(ByVal iIndex As Integer, ByVal strPattern As String) As Boolean
            Return Not (UCase(CStr(m_oNXArray(iIndex))) Like strPattern)
        End Function

        Public Function field_count() As Integer Implements IBrowseDataAdapter_.field_count
            Return 3
        End Function

        Public Overridable Sub MoveNext() Implements IBrowseDataAdapter_.MoveNext
            m_iPosition += 1
            Do While Not Me.EOF
                If Not m_oFilterArray(m_iPosition) Then
                    Exit Do
                End If
                m_iPosition += 1
            Loop
            m_iRecordNumber += 1
        End Sub
        Public Sub MovePrev() Implements IBrowseDataAdapter_.MovePrev
            m_iPosition -= 1
            Do While Not Me.BOF
                If Not m_oFilterArray(m_iPosition) Then
                    Exit Do
                End If
                m_iPosition -= 1
            Loop
            m_iRecordNumber -= 1
        End Sub
        Public Sub MoveBy(ByVal iRecordsToSkip As Integer) Implements IBrowseDataAdapter_.MoveBy
            'todo: mozliwa optymalizacja, gdy
            'nie ma zadnego filtra (nie bylo apply_filter
            'to m_iPosition == m_iRecordNumber i skok mozna zrobic 
            'od razu (odejmujac liczby, bez iteracji)
            'm_iPosition += iRecordsToSkip
            'm_iRecordNumber += iRecordsToSkip

            If iRecordsToSkip > 0 Then
                Do While iRecordsToSkip > 0 And Not Me.EOF
                    MoveNext()
                    iRecordsToSkip -= 1
                Loop
            Else
                Do While iRecordsToSkip < 0 And Not Me.BOF
                    MovePrev()
                    iRecordsToSkip += 1
                Loop
            End If
        End Sub
        Sub MoveTo(ByVal iRecordNumber As Integer) Implements IBrowseDataAdapter_.MoveTo
            MoveBy(iRecordNumber - m_iRecordNumber)
        End Sub

        Private Sub Reset()
            'search first not filtered
            m_iPosition = -1
            m_iRecordNumber = -1
            MoveNext()
        End Sub
        Public Sub apply_filter(ByVal strLike As String)
            strLike = UCase(strLike)
            For iter As Integer = 0 To m_oNXArray.count - 1
                m_oFilterArray(iter) = should_be_filtered(iter, strLike)
            Next
            Reset()
        End Sub
        Public Sub clean_filter()
            For iter As Integer = 0 To m_oNXArray.count - 1
                m_oFilterArray(iter) = False
            Next
            Reset()
        End Sub

        Protected m_oFilterArray As nxarray
        Protected m_oNXArray As nxarray
        Protected m_iPosition As Integer
        Protected m_iRecordNumber As Integer
    End Class

    'Browse Object With Info
    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_bowi)> _
    Public Class BOWI
        Implements IComparable

        Public Sub New()
            m_iIdObj = 0
            m_iTypeId = 0
            m_strText = ""
            m_oExtraInfo = Nothing
        End Sub

        Public Function CompareTo(ByVal oObject As Object) As Integer Implements System.IComparable.CompareTo
            Dim oBOWI As BOWI = oObject
            Return m_strText.CompareTo(oBOWI.m_strText)
        End Function

        Public Shared Function new_bowi(ByVal iTypeId As Integer, ByVal iIdObj As Integer, _
            ByVal strText As String, ByVal oExtraInfo As Object) As BOWI
            Dim oBOWI = New BOWI
            With oBOWI
                .m_iTypeId = iTypeId
                .m_iIdObj = iIdObj
                .m_strText = strText
                .m_oExtraInfo = oExtraInfo
            End With
            Return oBOWI
        End Function
        Public m_iIdObj As Integer
        Public m_iTypeId As Integer
        Public m_strText As String
        Public m_oExtraInfo As Object
    End Class

    <ComVisible(True), Guid(global_config.gc_guid_nx2ne2002_bowi_bda)> _
    Public Class BOWI_BDA
        Inherits NXArrayBDA
        Public Sub New(ByVal oNXArray As nxarray)
            MyBase.New(oNXArray)
        End Sub
        Public Overrides Function record_id() As Integer
            Return get_bowi(m_iPosition).m_iIdObj
        End Function
        Public Overrides Function record_type() As Integer
            Return get_bowi(m_iPosition).m_iTypeId
        End Function
        Public Overrides Function record_string() As String
            Return get_bowi(m_iPosition).m_strText
        End Function
        Public Overrides Function field(ByVal iIndex As Integer) As Object
            Select Case iIndex
                Case 0  'idobj
                    Return get_bowi(m_iPosition).m_iIdObj
                Case 1  'display value
                    Return get_bowi(m_iPosition).m_strText
                Case 2  'typeid
                    Return get_bowi(m_iPosition).m_iTypeId
                Case Else
                    Throw New nxexception("BOWI_BDA:field: invalid iIndex=" + iIndex.ToString())
            End Select
        End Function
        Private Function get_bowi(ByVal iIndex As Integer) As BOWI
            Return m_oNXArray(iIndex)
        End Function
        Public Overrides Function should_be_filtered(ByVal iIndex As Integer, ByVal strPattern As String) As Boolean
            Return Not (UCase(get_bowi(iIndex).m_strText) Like strPattern)
        End Function
    End Class
End Namespace