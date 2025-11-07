import { Button } from '@/components/ui/button';
import { useNavigate } from 'react-router-dom';
import { BookOpen, Search, Filter, Library, Sparkles } from 'lucide-react';

const Index = () => {
  const navigate = useNavigate();

  return (
    <div className="min-h-screen bg-gradient-to-br from-background via-background to-muted">
      {/* Hero Section */}
      <section className="container mx-auto px-4 py-20 text-center">
        <div className="max-w-4xl mx-auto space-y-8">
          <div className="inline-block p-4 bg-primary/10 rounded-full mb-4">
            <BookOpen className="w-16 h-16 text-primary" />
          </div>
          
          <h1 className="text-5xl md:text-7xl font-bold tracking-tight">
            Discover Your Next
            <span className="block gradient-primary bg-clip-text text-transparent mt-2">
              Great Read
            </span>
          </h1>
          
          <p className="text-xl text-muted-foreground max-w-2xl mx-auto leading-relaxed">
            Smart book recommendations powered by advanced filtering and AI. 
            Build your perfect reading list and explore thousands of titles.
          </p>

          <div className="flex flex-col sm:flex-row gap-4 justify-center pt-4">
            <Button 
              size="lg" 
              onClick={() => navigate('/auth')}
              className="text-lg px-8 py-6"
            >
              Get Started
              <Sparkles className="w-5 h-5 ml-2" />
            </Button>
            <Button 
              size="lg" 
              variant="outline"
              onClick={() => navigate('/auth')}
              className="text-lg px-8 py-6"
            >
              Sign In
            </Button>
          </div>
        </div>
      </section>

      {/* Features */}
      <section className="container mx-auto px-4 py-20">
        <div className="grid md:grid-cols-3 gap-8 max-w-5xl mx-auto">
          <div className="bg-card p-8 rounded-lg border text-center hover:shadow-lg transition-shadow">
            <div className="w-12 h-12 bg-primary/10 rounded-full flex items-center justify-center mx-auto mb-4">
              <Search className="w-6 h-6 text-primary" />
            </div>
            <h3 className="text-xl font-semibold mb-3">Smart Search</h3>
            <p className="text-muted-foreground">
              Describe what you're looking for and let AI find the perfect book for you.
            </p>
          </div>

          <div className="bg-card p-8 rounded-lg border text-center hover:shadow-lg transition-shadow">
            <div className="w-12 h-12 bg-primary/10 rounded-full flex items-center justify-center mx-auto mb-4">
              <Filter className="w-6 h-6 text-primary" />
            </div>
            <h3 className="text-xl font-semibold mb-3">Advanced Filters</h3>
            <p className="text-muted-foreground">
              Filter by author, year, genre, and more to find exactly what you need.
            </p>
          </div>

          <div className="bg-card p-8 rounded-lg border text-center hover:shadow-lg transition-shadow">
            <div className="w-12 h-12 bg-primary/10 rounded-full flex items-center justify-center mx-auto mb-4">
              <Library className="w-6 h-6 text-primary" />
            </div>
            <h3 className="text-xl font-semibold mb-3">Personal Library</h3>
            <p className="text-muted-foreground">
              Build and manage your reading list with books you want to read.
            </p>
          </div>
        </div>
      </section>

      {/* CTA */}
      <section className="container mx-auto px-4 py-20">
        <div className="max-w-3xl mx-auto text-center bg-card p-12 rounded-2xl border">
          <h2 className="text-3xl md:text-4xl font-bold mb-4">
            Start Your Reading Journey Today
          </h2>
          <p className="text-muted-foreground mb-8 text-lg">
            Join thousands of readers discovering their next favorite book.
          </p>
          <Button 
            size="lg" 
            onClick={() => navigate('/auth')}
            className="text-lg px-12 py-6"
          >
            Create Free Account
          </Button>
        </div>
      </section>
    </div>
  );
};

export default Index;
