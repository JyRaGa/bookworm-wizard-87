import { useState, useEffect } from 'react';
import { useNavigate } from 'react-router-dom';
import { BookCard } from '@/components/BookCard';
import { FilterBar } from '@/components/FilterBar';
import { Button } from '@/components/ui/button';
import { Tabs, TabsContent, TabsList, TabsTrigger } from '@/components/ui/tabs';
import { Book, FilterOptions } from '@/types/book';
import { booksAPI, readingListAPI, authAPI } from '@/services/api';
import { BookOpen, LogOut, Library } from 'lucide-react';
import { useToast } from '@/hooks/use-toast';

const Dashboard = () => {
  const [allBooks, setAllBooks] = useState<Book[]>([]);
  const [filteredBooks, setFilteredBooks] = useState<Book[]>([]);
  const [readingList, setReadingList] = useState<Book[]>([]);
  const [isLoading, setIsLoading] = useState(true);
  const navigate = useNavigate();
  const { toast } = useToast();

  useEffect(() => {
    const user = localStorage.getItem('user');
    if (!user) {
      navigate('/auth');
      return;
    }

    loadData();
  }, [navigate]);

  const loadData = async () => {
    try {
      const user = JSON.parse(localStorage.getItem('user') || '{}');
      const [books, reading] = await Promise.all([
        booksAPI.getAll(),
        readingListAPI.get(user.id)
      ]);
      setAllBooks(books);
      setFilteredBooks(books);
      setReadingList(reading);
    } catch (error) {
      toast({
        title: "Error",
        description: "Failed to load books",
        variant: "destructive",
      });
    } finally {
      setIsLoading(false);
    }
  };

  const handleFilter = async (filters: FilterOptions) => {
    setIsLoading(true);
    try {
      const filtered = await booksAPI.filter(filters);
      setFilteredBooks(filtered);
    } catch (error) {
      toast({
        title: "Error",
        description: "Failed to filter books",
        variant: "destructive",
      });
    } finally {
      setIsLoading(false);
    }
  };

  const handleLogout = async () => {
    await authAPI.logout();
    localStorage.removeItem('user');
    navigate('/');
  };

  const handleBookClick = (book: Book) => {
    toast({
      title: book.title,
      description: book.description,
    });
  };

  return (
    <div className="min-h-screen bg-background">
      {/* Header */}
      <header className="border-b bg-card sticky top-0 z-10">
        <div className="container mx-auto px-4 py-4">
          <div className="flex items-center justify-between">
            <div className="flex items-center gap-3">
              <div className="w-10 h-10 bg-primary rounded-full flex items-center justify-center">
                <BookOpen className="w-5 h-5 text-primary-foreground" />
              </div>
              <div>
                <h1 className="text-2xl font-bold">BookWise</h1>
                <p className="text-sm text-muted-foreground">Your Smart Reading Companion</p>
              </div>
            </div>
            <Button onClick={handleLogout} variant="outline">
              <LogOut className="w-4 h-4 mr-2" />
              Logout
            </Button>
          </div>
        </div>
      </header>

      {/* Main Content */}
      <main className="container mx-auto px-4 py-8">
        <Tabs defaultValue="browse" className="space-y-6">
          <TabsList className="grid w-full max-w-md grid-cols-2">
            <TabsTrigger value="browse">
              <Library className="w-4 h-4 mr-2" />
              Browse Books
            </TabsTrigger>
            <TabsTrigger value="reading-list">
              <BookOpen className="w-4 h-4 mr-2" />
              My Reading List ({readingList.length})
            </TabsTrigger>
          </TabsList>

          <TabsContent value="browse" className="space-y-6">
            <FilterBar onFilter={handleFilter} />
            
            {isLoading ? (
              <div className="text-center py-12">
                <p className="text-muted-foreground">Loading books...</p>
              </div>
            ) : filteredBooks.length === 0 ? (
              <div className="text-center py-12">
                <p className="text-muted-foreground">No books found matching your filters.</p>
              </div>
            ) : (
              <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-6">
                {filteredBooks.map((book) => (
                  <BookCard 
                    key={book.id} 
                    book={book}
                    onClick={() => handleBookClick(book)}
                  />
                ))}
              </div>
            )}
          </TabsContent>

          <TabsContent value="reading-list" className="space-y-6">
            {readingList.length === 0 ? (
              <div className="text-center py-12">
                <BookOpen className="w-16 h-16 mx-auto text-muted-foreground mb-4" />
                <p className="text-muted-foreground">Your reading list is empty.</p>
                <p className="text-sm text-muted-foreground">Start adding books to build your collection!</p>
              </div>
            ) : (
              <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-6">
                {readingList.map((book) => (
                  <BookCard 
                    key={book.id} 
                    book={book}
                    onClick={() => handleBookClick(book)}
                  />
                ))}
              </div>
            )}
          </TabsContent>
        </Tabs>
      </main>
    </div>
  );
};

export default Dashboard;
